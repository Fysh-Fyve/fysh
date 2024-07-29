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
#include "Variable.h"

#include <llvm/Analysis/CGSCCPassManager.h>
#include <llvm/Analysis/LoopAnalysisManager.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/StandardInstrumentations.h>
#include <variant>

namespace fysh {
using Emit = std::variant<llvm::Value *, ast::Error>;
using Params = std::vector<llvm::Type *>;

struct Options {
  enum class Output { AST, IR } output = Output::IR;
  bool noOpt = false;
  std::string outputFilename = "-";
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
  Emit binary(const ast::FyshBinaryExpr &expr);
  Emit anchorIn(const ast::FyshBinaryExpr &expr);
  Emit anchorOut(const ast::FyshBinaryExpr &expr);
  Emit unary(const ast::FyshUnaryExpr &expr);
  Emit call(const ast::FyshCallExpr &expr);
  Emit grilledFysh();

  /* Compiling subroutines */
  std::optional<ast::Error> subroutine(const ast::SUBroutine &sub, bool noOpt);

  /* Utility methods */
  Variable resolveVariable(const std::string_view &name,
                           Definition define = Definition::NONE);
  llvm::Type *intTy() { return llvm::Type::getInt32Ty(*context); };
  llvm::Type *floatTy() { return llvm::Type::getFloatTy(*context); };
  llvm::Type *voidTy() { return llvm::Type::getVoidTy(*context); };
  llvm::Function *define(const std::string_view &name, llvm::Type *returnType,
                         std::vector<llvm::Type *> params);
  llvm::Function *getOrDefine(const std::string_view &name,
                              llvm::Type *returnType,
                              std::vector<llvm::Type *> params);

  llvm::Function *getFunction(const std::string_view &name);
  void defineGlobals(const std::vector<ast::FyshStmt> &statements);

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

inline constexpr llvm::Value *unwrap(const fysh::Emit &v) {
  return std::get<llvm::Value *>(v);
}

inline constexpr bool isError(const fysh::Emit &emit) {
  return std::holds_alternative<fysh::ast::Error>(emit);
}

}; // namespace fysh

#endif // !FYSH_COMPYLER_H_
