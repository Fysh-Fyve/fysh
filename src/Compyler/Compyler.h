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

#include "../AST/AST.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
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

namespace fysh {
using Emit = std::variant<llvm::Value *, ast::Error>;
class Compyler {
public:
  Compyler();

  llvm::Function *compyle(const std::vector<ast::FyshStmt> &program);

private:
  /* Compiling statements */
  Emit statement(const ast::FyshStmt &stmt, llvm::Function *fn);
  Emit block(const std::vector<ast::FyshStmt> &block, llvm::Function *fn);
  Emit ifStmt(const ast::FyshIfStmt &stmt, llvm::Function *fn);
  Emit loop(const ast::FyshLoopStmt &stmt, llvm::Function *fn);
  Emit increment(const ast::FyshIncrementStmt &stmt, llvm::Function *fn);
  Emit decrement(const ast::FyshDecrementStmt &stmt, llvm::Function *fn);
  Emit assignment(const ast::FyshAssignmentStmt &stmt, llvm::Function *fn);

  /* Compiling expressions */
  Emit expression(const ast::FyshExpr *expr);
  Emit identifier(const ast::FyshIdentifier &expr);
  Emit binary(const fysh::ast::FyshBinaryExpr &expr);
  Emit unary(const fysh::ast::FyshUnaryExpr &expr);

  std::unordered_map<std::string_view, llvm::AllocaInst *> namedValues;
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
