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
 * \file CompyleStatements.cc
 */
#include "Compyler.h"

fysh::Emit fysh::Compyler::squidStmt(const fysh::ast::Squid &stmt) {
  Emit retVal = expression(&stmt.expr);
  if (isError(retVal)) {
    return retVal;
  }
  llvm::Value *val{unwrap(retVal)};
  builder->CreateRet(val);
  return val;
}

fysh::Emit fysh::Compyler::anchorStmt(const fysh::ast::FyshAnchorStmt &stmt) {
  if (stmt.op == fysh::ast::FyshBinary::AnchorIn) {
    // Only handle assignments to identifiers for now
    if (const ast::FyshIdentifier *ident =
            std::get_if<ast::FyshIdentifier>(&stmt.right)) {
      fysh::Variable variable{resolveVariable(ident->name, Definition::LOCAL)};
      // int fysh_gpio_read_all()
      llvm::Function *func{
          getOrDefine("fysh_gpio_read_all", intTy(), Params{})};
      llvm::Value *retVal{builder->CreateCall(func->getFunctionType(), func,
                                              std::vector<llvm::Value *>())};
      builder->CreateStore(retVal, variable.val());
      return retVal;
    } else {
      return ast::Error{"assigning to non-variable"};
    }
  } else if (stmt.op == fysh::ast::FyshBinary::AnchorOut) {
    Emit val{expression(&stmt.right)};
    if (llvm::Value * *expr{std::get_if<llvm::Value *>(&val)}) {
      // void fysh_gpio_write_all(int value)
      llvm::Function *func{
          getOrDefine("fysh_gpio_write_all", voidTy(), Params{intTy()})};
      llvm::Value *retVal{builder->CreateCall(
          func->getFunctionType(), func, std::vector<llvm::Value *>{*expr})};
      return *expr;
    } else {
      return val;
    }
  } else {
    return ast::Error{"invalid anchor operand"};
  }
}

fysh::Emit fysh::Compyler::loop(const fysh::ast::FyshLoopStmt &stmt) {
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
  if (isError(condEmit)) {
    return condEmit;
  }
  llvm::Value *loopCond{unwrap(condEmit)};

  builder->CreateCondBr(builder->CreateICmpNE(loopCond, builder->getInt32(0)),
                        loopBodyBlock, loopExit);
  builder->SetInsertPoint(loopBodyBlock);
  Emit blockEmit{block(stmt.body)};
  if (isError(blockEmit)) {
    return blockEmit;
  }
  builder->CreateBr(conditionBlock);
  builder->SetInsertPoint(loopExit);

  return unwrap(blockEmit);
}

fysh::Emit fysh::Compyler::increment(const fysh::ast::FyshIncrementStmt &stmt) {
  if (const ast::FyshIdentifier *ident =
          std::get_if<ast::FyshIdentifier>(&stmt.expr)) {
    Variable variable{resolveVariable(ident->name)};
    if (!variable) {
      return ast::Error{"unknown variable"};
    }
    llvm::Value *load{
        builder->CreateLoad(variable.type(), variable.val(), ident->name)};
    llvm::Value *inc{builder->CreateAdd(load, builder->getInt32(1))};
    builder->CreateStore(inc, variable.val());
    return inc;
  } else {
    return ast::Error{"incrementing non-variable"};
  }
}

fysh::Emit fysh::Compyler::decrement(const fysh::ast::FyshDecrementStmt &stmt) {
  if (const ast::FyshIdentifier *ident =
          std::get_if<ast::FyshIdentifier>(&stmt.expr)) {
    Variable variable{resolveVariable(ident->name)};
    if (!variable) {
      return ast::Error{"unknown variable"};
    }
    llvm::Value *load{
        builder->CreateLoad(variable.type(), variable.val(), ident->name)};
    llvm::Value *dec{builder->CreateSub(load, builder->getInt32(1))};
    builder->CreateStore(dec, variable.val());
    return dec;
  } else {
    return ast::Error{"decrementing non-variable"};
  }
}

fysh::Emit
fysh::Compyler::assignment(const fysh::ast::FyshAssignmentStmt &stmt) {
  // Only handle assignments to identifiers for now
  if (const ast::FyshIdentifier *ident =
          std::get_if<ast::FyshIdentifier>(&stmt.left)) {
    Variable variable{resolveVariable(ident->name, Definition::LOCAL)};
    Emit val{expression(&stmt.right)};
    if (isError(val)) {
      return val;
    }
    builder->CreateStore(unwrap(val), variable.val());
    return unwrap(val);
  } else {
    return ast::Error{"assigning to non-variable"};
  }
}

fysh::Emit fysh::Compyler::statement(const ast::FyshStmt &stmt) {
  return std::visit(
      [this](auto &&arg) -> fysh::Emit {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, ast::Error>) {
          return arg;
        } else if constexpr (std::is_same_v<T, ast::FyshExpr>) {
          return expression(&arg);
        } else if constexpr (std::is_same_v<T, ast::FyshBlock>) {
          return block(arg.statements);
        } else if constexpr (std::is_same_v<T, ast::FyshLoopStmt>) {
          return loop(arg);
        } else if constexpr (std::is_same_v<T, ast::FyshIfStmt>) {
          return ifStmt(arg);
        } else if constexpr (std::is_same_v<T, ast::FyshIncrementStmt>) {
          return increment(arg);
        } else if constexpr (std::is_same_v<T, ast::FyshDecrementStmt>) {
          return decrement(arg);
        } else if constexpr (std::is_same_v<T, ast::FyshAssignmentStmt>) {
          return assignment(arg);
        } else if constexpr (std::is_same_v<T, ast::FyshAnchorStmt>) {
          return anchorStmt(arg);
        } else if constexpr (std::is_same_v<T, ast::Squid>) {
          return squidStmt(arg);
        } else if constexpr (std::is_same_v<T, ast::BrokenFysh>) {
          return nullptr;
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      stmt);
}

fysh::Emit
fysh::Compyler::block(const std::vector<fysh::ast::FyshStmt> &block) {
  llvm::Value *retVal{nullptr}; // Initialize retVal explicitly

  for (const ast::FyshStmt &stmt : block) {
    fysh::Emit emit{statement(stmt)};
    if (isError(emit)) {
      return emit;
    } else if (llvm::Value *expr = unwrap(emit)) {
      retVal = expr;
    }
  }

  // Return the last expression's value or nullptr if no expressions were
  // executed.
  return retVal;
}

fysh::Emit fysh::Compyler::ifStmt(const fysh::ast::FyshIfStmt &stmt) {
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
  if (isError(condEmit)) {
    return condEmit;
  }
  llvm::Value *ifCond{unwrap(condEmit)};

  builder->CreateCondBr(ifCond, thenBlock, elseBlock ? elseBlock : exitBlock);

  builder->SetInsertPoint(thenBlock);
  Emit thenEmit{block(stmt.consequence)};
  if (isError(thenEmit)) {
    return thenEmit;
  }
  builder->CreateBr(exitBlock);
  if (elseBlock) {
    builder->SetInsertPoint(elseBlock);
    Emit elseEmit{block(stmt.consequence)};
    if (isError(elseEmit)) {
      return elseEmit;
    }
    builder->CreateBr(exitBlock);
    elseBlock = builder->GetInsertBlock();
    builder->SetInsertPoint(exitBlock);
    llvm::PHINode *phiNode = builder->CreatePHI(intTy(), 2, "iftmp");
    phiNode->addIncoming(unwrap(thenEmit), thenBlock);
    phiNode->addIncoming(unwrap(elseEmit), elseBlock);
    return phiNode;
  } else {
    builder->SetInsertPoint(exitBlock);
    llvm::PHINode *phiNode = builder->CreatePHI(intTy(), 2, "iftmp");
    phiNode->addIncoming(unwrap(thenEmit), thenBlock);
    phiNode->addIncoming(builder->getInt32(0), conditionBlock);
    return phiNode;
  }
}
