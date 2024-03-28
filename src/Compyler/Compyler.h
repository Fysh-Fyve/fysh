/**
 * Copyright (C) 2024 Yahya Al-Shamali, Kyle Prince, Charles Ancheta
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * \file Compyler.h
 */
#ifndef FYSH_COMPYLER_H_
#define FYSH_COMPYLER_H_

#include "../Parser/AST/AST.h"

#include <llvm/IR/Argument.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/StandardInstrumentations.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Scalar/Reassociate.h>
#include <llvm/Transforms/Scalar/SimplifyCFG.h>
#include <variant>

namespace fysh {
using Emit = std::variant<llvm::Value *, ast::Error>;
llvm::Value *unwrap(const Emit &v);

struct Options {
  enum class Output { AST, IR } output;
  bool noOpt = false;
  std::string outputFilename = "-";
};

struct Undefined {};

struct Variable : std::variant<llvm::GlobalVariable *, llvm::AllocaInst *,
                               llvm::Argument *, Undefined> {
  bool operator!() { return std::holds_alternative<Undefined>(*this); }

  llvm::Type *type() {
    return std::visit(
        [](auto &&arg) -> llvm::Type * {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, llvm::GlobalVariable *>) {
            return arg->getValueType();
          } else if constexpr (std::is_same_v<T, llvm::AllocaInst *>) {
            return arg->getAllocatedType();
          } else if constexpr (std::is_same_v<T, llvm::Argument *>) {
            return arg->getType();
          } else if constexpr (std::is_same_v<T, fysh::Undefined>) {
            return nullptr;
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        *this);
  }

  constexpr llvm::Value *val() {
    return std::visit(
        [](auto &&arg) -> llvm::Value * {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, llvm::GlobalVariable *>) {
            return arg;
          } else if constexpr (std::is_same_v<T, llvm::AllocaInst *>) {
            return arg;
          } else if constexpr (std::is_same_v<T, llvm::Argument *>) {
            return arg;
          } else if constexpr (std::is_same_v<T, fysh::Undefined>) {
            return nullptr;
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        *this);
  }
};

enum class Definition { LOCAL, GLOBAL, NONE };

class Compyler {
public:
  Compyler(std::string filename);
  void compyle(const ast::FyshProgram &ast, Options opts);

private:
  /* Compiling statements */
  Emit statement(const ast::FyshStmt &stmt);
  Emit block(const std::vector<ast::FyshStmt> &block);
  Emit ifStmt(const ast::FyshIfStmt &stmt);
  Emit squidStmt(const ast::Squid &stmt);
  Emit loop(const ast::FyshLoopStmt &stmt);
  Emit increment(const ast::FyshIncrementStmt &stmt);
  Emit decrement(const ast::FyshDecrementStmt &stmt);
  Emit assignment(const ast::FyshAssignmentStmt &stmt);
  Emit anchorStmt(const ast::FyshAnchorStmt &stmt);

  /* Compiling expressions */
  Emit expression(const ast::FyshExpr *expr);
  Emit identifier(const ast::FyshIdentifier &expr);
  Emit binary(const fysh::ast::FyshBinaryExpr &expr);
  Emit anchorIn(const fysh::ast::FyshBinaryExpr &expr);
  Emit anchorOut(const fysh::ast::FyshBinaryExpr &expr);
  Emit unary(const fysh::ast::FyshUnaryExpr &expr);
  Emit call(const fysh::ast::FyshCallExpr &expr);
  Emit grilledFysh();

  /* Compiling subroutines */

  std::optional<fysh::ast::Error> subroutine(const fysh::ast::SUBroutine &sub,
                                             bool noOpt);

  /* Utility methods */
  Variable resolveVariable(const std::string_view &name, Definition define);
  llvm::Type *intTy() { return llvm::Type::getInt32Ty(*context); };
  llvm::Type *floatTy() { return llvm::Type::getFloatTy(*context); };
  llvm::Type *voidTy() { return llvm::Type::getVoidTy(*context); };
  llvm::Function *define(const std::string_view &name, llvm::Type *returnType,
                         std::vector<llvm::Type *> params);
  llvm::Function *getOrDefine(const std::string_view &name,
                              llvm::Type *returnType,
                              std::vector<llvm::Type *> params);

  llvm::Function *getFunction(const std::string_view &name);

  /* Current program's global variables */
  std::unordered_map<std::string_view, llvm::GlobalVariable *> globals;
  /* Current subroutines's local variables */
  std::unordered_map<std::string_view, llvm::AllocaInst *> locals;
  /* Current subroutines's arguments */
  std::unordered_map<std::string_view, llvm::Argument *> args;
  /* Current module's subroutines */
  std::unordered_map<std::string_view, llvm::Function *> subs;

  /* LLVM stuff */
  std::unique_ptr<llvm::LLVMContext> context;
  std::unique_ptr<llvm::Module> module;
  std::unique_ptr<llvm::IRBuilder<>> builder;
  std::unique_ptr<llvm::FunctionPassManager> fpm;
  std::unique_ptr<llvm::LoopAnalysisManager> lam;
  std::unique_ptr<llvm::FunctionAnalysisManager> fam;
  std::unique_ptr<llvm::CGSCCAnalysisManager> cgam;
  std::unique_ptr<llvm::ModuleAnalysisManager> mam;
  std::unique_ptr<llvm::PassInstrumentationCallbacks> pic;
  std::unique_ptr<llvm::StandardInstrumentations> si;
};

}; // namespace fysh

#endif // !FYSH_COMPYLER_H_
