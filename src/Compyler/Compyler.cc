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
 * \file Compyler.cc
 */
#include "Compyler.h"
#include "../AST/AST.h"

#include <iostream>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <unordered_map>
#include <variant>

fysh::Compyler::Compyler()
    : context{std::make_unique<llvm::LLVMContext>()},
      module{std::make_unique<llvm::Module>("fysh", *context)},
      builder{std::make_unique<llvm::IRBuilder<>>(*context)},
      fpm{std::make_unique<llvm::FunctionPassManager>()},
      lam{std::make_unique<llvm::LoopAnalysisManager>()},
      fam{std::make_unique<llvm::FunctionAnalysisManager>()},
      cgam{std::make_unique<llvm::CGSCCAnalysisManager>()},
      mam{std::make_unique<llvm::ModuleAnalysisManager>()},
      pic{std::make_unique<llvm::PassInstrumentationCallbacks>()},
      si{std::make_unique<llvm::StandardInstrumentations>(
          *context, /*DebugLogging*/ true)} {

  // Add transform passes.
  // Do simple "peephole" optimizations and bit-twiddling optzns.
  fpm->addPass(llvm::InstCombinePass());
  // Reassociate expressions.
  fpm->addPass(llvm::ReassociatePass());
  // Eliminate Common SubExpressions.
  fpm->addPass(llvm::GVNPass());
  // Simplify the control flow graph (deleting unreachable blocks, etc).
  fpm->addPass(llvm::SimplifyCFGPass());

  llvm::PassBuilder pb;
  pb.registerModuleAnalyses(*mam);
  pb.registerFunctionAnalyses(*fam);
  pb.crossRegisterProxies(*lam, *fam, *cgam, *mam);
}

fysh::Emit fysh::Compyler::ifStmt(const fysh::ast::FyshIfStmt &stmt,
                                  llvm::Function *fn) {
  llvm::Function *parent{builder->GetInsertBlock()->getParent()};
  llvm::BasicBlock *conditionBlock{
      llvm::BasicBlock::Create(*context, "if_cond", parent)};
  llvm::BasicBlock *thenBlock{
      llvm::BasicBlock::Create(*context, "then", parent)};
  llvm::BasicBlock *elseBlock{
      stmt.alternative.has_value()
          ? llvm::BasicBlock::Create(*context, "else", parent)
          : nullptr};
  llvm::BasicBlock *exitBlock{
      llvm::BasicBlock::Create(*context, "if_exit", parent)};

  builder->CreateBr(conditionBlock);

  builder->SetInsertPoint(conditionBlock);
  Emit condEmit{expression(&stmt.condition)};
  if (std::holds_alternative<ast::Error>(condEmit)) {
    return condEmit;
  }
  llvm::Value *ifCond{std::get<llvm::Value *>(condEmit)};

  builder->CreateCondBr(ifCond, thenBlock, elseBlock ? elseBlock : exitBlock);

  builder->SetInsertPoint(thenBlock);
  Emit thenEmit{block(stmt.consequence, fn)};
  if (std::holds_alternative<ast::Error>(thenEmit)) {
    return thenEmit;
  }
  builder->CreateBr(exitBlock);
  if (elseBlock) {
    builder->SetInsertPoint(elseBlock);
    Emit elseEmit{block(stmt.consequence, fn)};
    if (std::holds_alternative<ast::Error>(elseEmit)) {
      return elseEmit;
    }
    builder->CreateBr(exitBlock);
    elseBlock = builder->GetInsertBlock();
    builder->SetInsertPoint(exitBlock);
    llvm::PHINode *phiNode =
        builder->CreatePHI(llvm::Type::getInt32Ty(*context), 2, "iftmp");
    phiNode->addIncoming(std::get<llvm::Value *>(thenEmit), thenBlock);
    phiNode->addIncoming(std::get<llvm::Value *>(elseEmit), elseBlock);
    return phiNode;
  } else {
    builder->SetInsertPoint(exitBlock);
    llvm::PHINode *phiNode =
        builder->CreatePHI(llvm::Type::getInt32Ty(*context), 2, "iftmp");
    phiNode->addIncoming(std::get<llvm::Value *>(thenEmit), thenBlock);
    phiNode->addIncoming(llvm::ConstantInt::get(*context, llvm::APInt(32, 0)),
                         conditionBlock);
    return phiNode;
  }
}

fysh::Emit fysh::Compyler::loop(const fysh::ast::FyshLoopStmt &stmt,
                                llvm::Function *fn) {
  llvm::Function *parent{builder->GetInsertBlock()->getParent()};

  llvm::BasicBlock *conditionBlock{
      llvm::BasicBlock::Create(*context, "loop_cond", parent)};
  llvm::BasicBlock *loopBodyBlock{
      llvm::BasicBlock::Create(*context, "loop_body", parent)};
  llvm::BasicBlock *loopExit{
      llvm::BasicBlock::Create(*context, "loop_exit", parent)};

  builder->CreateBr(conditionBlock);

  builder->SetInsertPoint(conditionBlock);
  Emit condEmit{expression(&stmt.condition)};
  if (std::holds_alternative<ast::Error>(condEmit)) {
    return condEmit;
  }
  llvm::Value *loopCond{std::get<llvm::Value *>(condEmit)};

  builder->CreateCondBr(loopCond, loopBodyBlock, loopExit);
  builder->SetInsertPoint(loopBodyBlock);
  Emit blockEmit{block(stmt.body, fn)};
  if (std::holds_alternative<ast::Error>(blockEmit)) {
    return blockEmit;
  }
  builder->CreateBr(conditionBlock);
  builder->SetInsertPoint(loopExit);

  return std::get<llvm::Value *>(blockEmit);
}

fysh::Emit fysh::Compyler::increment(const fysh::ast::FyshIncrementStmt &stmt,
                                     llvm::Function *fn) {
  if (const ast::FyshIdentifier *ident =
          std::get_if<ast::FyshIdentifier>(&stmt.expr)) {
    if (namedValues.find(ident->name) == namedValues.end()) {
      return ast::Error{"unknown variable"};
    }
    llvm::AllocaInst *alloca{namedValues[ident->name]};
    llvm::Value *load{
        builder->CreateLoad(alloca->getAllocatedType(), alloca, ident->name)};
    llvm::Value *inc{builder->CreateAdd(load, builder->getInt32(1))};
    builder->CreateStore(inc, alloca);
    return inc;
  } else {
    return ast::Error{"incrementing non-variable"};
  }
}

fysh::Emit fysh::Compyler::decrement(const fysh::ast::FyshDecrementStmt &stmt,
                                     llvm::Function *fn) {
  if (const ast::FyshIdentifier *ident =
          std::get_if<ast::FyshIdentifier>(&stmt.expr)) {
    if (namedValues.find(ident->name) == namedValues.end()) {
      return ast::Error{"unknown variable"};
    }
    llvm::AllocaInst *alloca{namedValues[ident->name]};
    llvm::Value *load{
        builder->CreateLoad(alloca->getAllocatedType(), alloca, ident->name)};
    llvm::Value *dec{builder->CreateSub(load, builder->getInt32(1))};
    builder->CreateStore(dec, alloca);
    return dec;
  } else {
    return ast::Error{"decrementing non-variable"};
  }
}

fysh::Emit fysh::Compyler::assignment(const fysh::ast::FyshAssignmentStmt &stmt,
                                      llvm::Function *fn) {
  // Only handle assignments to identifiers for now
  if (const ast::FyshIdentifier *ident =
          std::get_if<ast::FyshIdentifier>(&stmt.left)) {
    if (namedValues.find(ident->name) == namedValues.end()) {
      namedValues[ident->name] = builder->CreateAlloca(
          llvm::Type::getInt32Ty(*context), nullptr, ident->name);
    }
    llvm::AllocaInst *alloca{namedValues[ident->name]};
    Emit val{expression(&stmt.right)};
    if (llvm::Value * *expr{std::get_if<llvm::Value *>(&val)}) {
      builder->CreateStore(*expr, alloca);
      return *expr;
    }
    return nullptr;
  } else {
    return ast::Error{"assigning to non-variable"};
  }
}

fysh::Emit fysh::Compyler::statement(const ast::FyshStmt &stmt,
                                     llvm::Function *fn) {
  return std::visit(
      [this, fn](auto &&arg) -> fysh::Emit {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, ast::Error>) {
          return arg;
        } else if constexpr (std::is_same_v<T, ast::FyshExpr>) {
          return expression(&arg);
        } else if constexpr (std::is_same_v<T, ast::FyshBlock>) {
          return block(arg, fn);
        } else if constexpr (std::is_same_v<T, ast::FyshLoopStmt>) {
          return loop(arg, fn);
        } else if constexpr (std::is_same_v<T, ast::FyshIfStmt>) {
          return ifStmt(arg, fn);
        } else if constexpr (std::is_same_v<T, ast::FyshIncrementStmt>) {
          return increment(arg, fn);
        } else if constexpr (std::is_same_v<T, ast::FyshDecrementStmt>) {
          return decrement(arg, fn);
        } else if constexpr (std::is_same_v<T, ast::FyshAssignmentStmt>) {
          return assignment(arg, fn);
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      stmt);
}

fysh::Emit fysh::Compyler::block(const std::vector<fysh::ast::FyshStmt> &block,
                                 llvm::Function *fn) {
  llvm::Value *retVal{nullptr}; // Initialize retVal explicitly

  for (const ast::FyshStmt &stmt : block) {
    fysh::Emit emit{statement(stmt, fn)};
    if (const ast::Error * error{std::get_if<ast::Error>(&emit)}) {
      return *error;
    }
    if (llvm::Value * *expr{std::get_if<llvm::Value *>(&emit)}) {
      retVal = *expr;
    }
  }

  // Return the last expression's value or nullptr if no expressions were
  // executed.
  return retVal;
}

llvm::Function *
fysh::Compyler::compyle(const std::vector<fysh::ast::FyshStmt> &program,
                        bool noOpt) {
  // int() function type
  llvm::FunctionType *ft{llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*context), std::vector<llvm::Type *>(), false)};
  llvm::Function *prototype{llvm::Function::Create(
      ft, llvm::Function::ExternalLinkage, "main", module.get())};

  llvm::BasicBlock *bb{llvm::BasicBlock::Create(*context, "entry", prototype)};
  builder->SetInsertPoint(bb);

  Emit emit{block(program, prototype)};

  if (llvm::Value * *expr{std::get_if<llvm::Value *>(&emit)}) {
    // Finish off the function.
    builder->CreateRet(*expr);
    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*prototype);

    if (!noOpt) {
      fpm->run(*prototype, *fam);
    }

    return prototype;
  } else if (const ast::Error * error{std::get_if<ast::Error>(&emit)}) {
    std::cerr << error << std::endl;
  }

  // Something went wrong!
  prototype->eraseFromParent();
  return nullptr;
}

fysh::Emit fysh::Compyler::unary(const fysh::ast::FyshUnaryExpr &expr) {
  Emit emit{expression(&expr.expr)};
  if (const ast::Error * err{std::get_if<ast::Error>(&emit)}) {
    return *err;
  }
  if (expr.op == ast::FyshUnary::Neg) {
    return builder->CreateNeg(std::get<llvm::Value *>(emit));
  }
  return nullptr;
}

fysh::Emit fysh::Compyler::binary(const fysh::ast::FyshBinaryExpr &expr) {
  fysh::Emit left{expression(&expr.left)};
  fysh::Emit right{expression(&expr.right)};
  if (const ast::Error * err{std::get_if<ast::Error>(&left)}) {
    return *err;
  }
  if (const ast::Error * err{std::get_if<ast::Error>(&right)}) {
    return *err;
  }
  llvm::Value *leftVal{std::get<llvm::Value *>(left)};
  llvm::Value *rightVal{std::get<llvm::Value *>(right)};

  if (expr.op == ast::FyshBinary::Add) {
    return builder->CreateAdd(leftVal, rightVal, "addtmp");
  }

  if (expr.op == ast::FyshBinary::Mul) {
    return builder->CreateMul(leftVal, rightVal, "multmp");
  }

  if (expr.op == ast::FyshBinary::Div) {
    return builder->CreateSDiv(leftVal, rightVal, "divtmp");
  }

  if (expr.op == ast::FyshBinary::GT) {
    return builder->CreateICmpSGT(leftVal, rightVal, "gttmp");
  }

  if (expr.op == ast::FyshBinary::Equal) {
    return builder->CreateICmpEQ(leftVal, rightVal, "eqtmp");
  }

  if (expr.op == ast::FyshBinary::NotEqual) {
    return builder->CreateICmpNE(leftVal, rightVal, "netmp");
  }

  if (expr.op == ast::FyshBinary::LT) {
    return builder->CreateICmpSLT(leftVal, rightVal, "lttmp");
  }

  if (expr.op == ast::FyshBinary::LTE) {
    return builder->CreateICmpSLE(leftVal, rightVal, "ltetmp");
  }

  if (expr.op == ast::FyshBinary::GTE) {
    return builder->CreateICmpSGE(leftVal, rightVal, "gtetmp");
  }

  if (expr.op == ast::FyshBinary::BitwiseAnd) {
    return builder->CreateAnd(leftVal, rightVal, "andtmp");
  }

  if (expr.op == ast::FyshBinary::BitwiseOr) {
    return builder->CreateOr(leftVal, rightVal, "ortmp");
  }

  if (expr.op == ast::FyshBinary::BitwiseXor) {
    return builder->CreateXor(leftVal, rightVal, "xortmp");
  }

  if (expr.op == ast::FyshBinary::ShiftLeft) {
    return builder->CreateShl(leftVal, rightVal, "shltmp");
  }

  if (expr.op == ast::FyshBinary::ShiftRight) {
    return builder->CreateAShr(leftVal, rightVal, "ashrtmp");
  }

  // TODO Any remaining binary expressions
  return nullptr;
}

fysh::Emit fysh::Compyler::identifier(const fysh::ast::FyshIdentifier &expr) {
  if (namedValues.find(expr.name) == namedValues.end()) {
    return ast::Error{"unknown variable"};
  }
  llvm::AllocaInst *alloc{namedValues[expr.name]};
  return builder->CreateLoad(alloc->getAllocatedType(), alloc, expr.name);
}

fysh::Emit fysh::Compyler::expression(const fysh::ast::FyshExpr *expr) {
  if (expr == nullptr) {
    return nullptr;
  }
  return std::visit(
      [this](auto &&arg) -> fysh::Emit {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, ast::Error>) {
          return arg;
        } else if constexpr (std::is_same_v<T, Box<ast::FyshBinaryExpr>>) {
          return binary(arg.getraw());
        } else if constexpr (std::is_same_v<T, Box<ast::FyshUnaryExpr>>) {
          return unary(arg.getraw());
        } else if constexpr (std::is_same_v<T, ast::FyshIdentifier>) {
          return identifier(arg);
        } else if constexpr (std::is_same_v<T, ast::FyshLiteral>) {
          return llvm::ConstantInt::get(*context, llvm::APInt(32, arg.num));
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      *expr);
}
