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

static constexpr bool isError(const fysh::Emit &emit) {
  return std::holds_alternative<fysh::ast::Error>(emit);
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
  if (isError(condEmit)) {
    return condEmit;
  }
  llvm::Value *ifCond{std::get<llvm::Value *>(condEmit)};

  builder->CreateCondBr(ifCond, thenBlock, elseBlock ? elseBlock : exitBlock);

  builder->SetInsertPoint(thenBlock);
  Emit thenEmit{block(stmt.consequence, fn)};
  if (isError(thenEmit)) {
    return thenEmit;
  }
  builder->CreateBr(exitBlock);
  if (elseBlock) {
    builder->SetInsertPoint(elseBlock);
    Emit elseEmit{block(stmt.consequence, fn)};
    if (isError(elseEmit)) {
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

static llvm::Function *defineReadAll(llvm::Module *module,
                                     llvm::LLVMContext *context) {
  // int fysh_gpio_read_all()
  llvm::FunctionType *ft{llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*context), std::vector<llvm::Type *>(), false)};
  return llvm::Function::Create(ft, llvm::Function::ExternalLinkage,
                                "fysh_gpio_read_all", module);
}

static llvm::Function *defineRead(llvm::Module *module,
                                  llvm::LLVMContext *context) {
  // int fysh_gpio_read(int pin)
  llvm::FunctionType *ft{llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*context),
      std::vector<llvm::Type *>{llvm::Type::getInt32Ty(*context)}, false)};
  return llvm::Function::Create(ft, llvm::Function::ExternalLinkage,
                                "fysh_gpio_read", module);
}

static llvm::Function *defineWriteAll(llvm::Module *module,
                                      llvm::LLVMContext *context) {
  // void fysh_gpio_write_all(int value)
  llvm::FunctionType *ft{llvm::FunctionType::get(
      llvm::Type::getVoidTy(*context),
      std::vector<llvm::Type *>{llvm::Type::getInt32Ty(*context)}, false)};
  return llvm::Function::Create(ft, llvm::Function::ExternalLinkage,
                                "fysh_gpio_write_all", module);
}

static llvm::Function *defineWrite(llvm::Module *module,
                                   llvm::LLVMContext *context) {
  // void fysh_gpio_write(int pin, int value)
  llvm::FunctionType *ft{llvm::FunctionType::get(
      llvm::Type::getVoidTy(*context),
      std::vector<llvm::Type *>{llvm::Type::getInt32Ty(*context),
                                llvm::Type::getInt32Ty(*context)},
      false)};
  return llvm::Function::Create(ft, llvm::Function::ExternalLinkage,
                                "fysh_gpio_write", module);
}

fysh::Emit fysh::Compyler::anchorIn(const fysh::ast::FyshBinaryExpr &expr) {
  fysh::Emit pin{expression(&expr.left)};
  if (isError(pin)) {
    return pin;
  }
  if (const ast::FyshIdentifier *ident =
          std::get_if<ast::FyshIdentifier>(&expr.right)) {
    if (namedValues.find(ident->name) == namedValues.end()) {
      return ast::Error{"unknown variable"};
    }
    llvm::AllocaInst *alloca{namedValues[ident->name]};
    llvm::Function *fn = module->getFunction("fysh_gpio_read");
    if (!fn) {
      fn = defineRead(module.get(), context.get());
      p.add(module->getFunction("fysh_gpio_read"));
    }
    llvm::FunctionType *ft{llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*context),
        std::vector<llvm::Type *>{llvm::Type::getInt32Ty(*context)}, false)};
    llvm::Value *retVal{builder->CreateCall(
        ft, fn, std::vector<llvm::Value *>{std::get<llvm::Value *>(pin)})};
    builder->CreateStore(retVal, alloca);
    return retVal;
  } else {
    return ast::Error{"assigning to non-variable"};
  }
}

fysh::Emit fysh::Compyler::anchorOut(const fysh::ast::FyshBinaryExpr &expr) {
  fysh::Emit pin{expression(&expr.left)};
  if (isError(pin)) {
    return pin;
  }
  fysh::Emit value{expression(&expr.right)};
  if (isError(value)) {
    return value;
  }
  llvm::Function *fn = module->getFunction("fysh_gpio_write");
  if (!fn) {
    fn = defineWrite(module.get(), context.get());
    p.add(module->getFunction("fysh_gpio_write"));
  }
  llvm::FunctionType *ft{llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*context),
      std::vector<llvm::Type *>{llvm::Type::getInt32Ty(*context)}, false)};
  return builder->CreateCall(
      ft, fn,
      std::vector<llvm::Value *>{std::get<llvm::Value *>(pin),
                                 std::get<llvm::Value *>(value)});
}

fysh::Emit fysh::Compyler::anchorStmt(const fysh::ast::FyshAnchorStmt &stmt,
                                      llvm::Function *fn) {
  if (stmt.op == fysh::ast::FyshBinary::AnchorIn) {
    // Only handle assignments to identifiers for now
    if (const ast::FyshIdentifier *ident =
            std::get_if<ast::FyshIdentifier>(&stmt.right)) {
      if (namedValues.find(ident->name) == namedValues.end()) {
        return ast::Error{"unknown variable"};
      }
      llvm::AllocaInst *alloca{namedValues[ident->name]};
      llvm::Function *fn = module->getFunction("fysh_gpio_read_all");
      if (!fn) {
        fn = defineReadAll(module.get(), context.get());
        p.add(module->getFunction("fysh_gpio_read_all"));
      }
      llvm::FunctionType *ft{
          llvm::FunctionType::get(llvm::Type::getInt32Ty(*context),
                                  std::vector<llvm::Type *>(), false)};
      llvm::Value *retVal{
          builder->CreateCall(ft, fn, std::vector<llvm::Value *>())};
      builder->CreateStore(retVal, alloca);
      return retVal;
    } else {
      return ast::Error{"assigning to non-variable"};
    }
  } else if (stmt.op == fysh::ast::FyshBinary::AnchorOut) {
    Emit val{expression(&stmt.right)};
    if (llvm::Value * *expr{std::get_if<llvm::Value *>(&val)}) {
      llvm::Function *fn = module->getFunction("fysh_gpio_write_all");
      if (!fn) {
        fn = defineWriteAll(module.get(), context.get());
        p.add(module->getFunction("fysh_gpio_write_all"));
      }
      llvm::FunctionType *ft{llvm::FunctionType::get(
          llvm::Type::getVoidTy(*context),
          std::vector<llvm::Type *>{llvm::Type::getInt32Ty(*context)}, false)};
      llvm::Value *retVal{
          builder->CreateCall(ft, fn, std::vector<llvm::Value *>{*expr})};
      return *expr;
    } else {
      return val;
    }
  } else {
    return ast::Error{"invalid anchor operand"};
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
  if (isError(condEmit)) {
    return condEmit;
  }
  llvm::Value *loopCond{std::get<llvm::Value *>(condEmit)};

  builder->CreateCondBr(loopCond, loopBodyBlock, loopExit);
  builder->SetInsertPoint(loopBodyBlock);
  Emit blockEmit{block(stmt.body, fn)};
  if (isError(blockEmit)) {
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
        } else if constexpr (std::is_same_v<T, ast::FyshAnchorStmt>) {
          return anchorStmt(arg, fn);
        } else if constexpr (std::is_same_v<T, ast::BabySquid>) {
          return ast::Error{"unimplemented"};
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

fysh::Program fysh::Compyler::compyle(const fysh::ast::FyshProgram &ast,
                                      bool noOpt) {
  fysh::Program newProgram;
  p = newProgram;
  // int() function type
  llvm::FunctionType *ft{llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*context), std::vector<llvm::Type *>(), false)};
  llvm::Function *prototype{llvm::Function::Create(
      ft, llvm::Function::ExternalLinkage, "main", module.get())};

  llvm::BasicBlock *bb{llvm::BasicBlock::Create(*context, "entry", prototype)};
  builder->SetInsertPoint(bb);

  Emit emit;
  for (const auto &declarations : ast) {
    emit = {std::visit(
        [this, prototype](auto &&arg) -> Emit {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, ast::Error>) {
            std::cerr << arg.getraw() << std::endl;
          } else if constexpr (std::is_same_v<T, ast::FyshStmt>) {
            return statement(arg, prototype);
          } else if constexpr (std::is_same_v<T, ast::SUBroutine>) {
            return ast::Error{"unimplemented"};
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        declarations)};
  }

  if (llvm::Value * *expr{std::get_if<llvm::Value *>(&emit)}) {
    // Finish off the function.
    builder->CreateRet(*expr);
    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*prototype);

    if (!noOpt) {
      fpm->run(*prototype, *fam);
    }
    p.add(prototype);
    return p;
  } else if (const ast::Error * error{std::get_if<ast::Error>(&emit)}) {
    std::cerr << error->getraw() << std::endl;
  }

  // Something went wrong!
  prototype->eraseFromParent();
  return {};
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
  llvm::Value *l{std::get<llvm::Value *>(left)};
  llvm::Value *r{std::get<llvm::Value *>(right)};

  using FB = ast::FyshBinary;
  switch (expr.op) {
    // clang-format off
  case FB::Add:        return builder->CreateAdd(l, r, "addtmp");
  case FB::Mul:        return builder->CreateMul(l, r, "multmp");
  case FB::Div:        return builder->CreateSDiv(l, r, "divtmp");
  case FB::Equal:      return builder->CreateICmpEQ(l, r, "eqtmp");
  case FB::NotEqual:   return builder->CreateICmpNE(l, r, "netmp");
  case FB::GT:         return builder->CreateICmpSGT(l, r, "gttmp");
  case FB::LT:         return builder->CreateICmpSLT(l, r, "lttmp");
  case FB::GTE:        return builder->CreateICmpSGE(l, r, "gtetmp");
  case FB::LTE:        return builder->CreateICmpSLE(l, r, "ltetmp");
  case FB::BitwiseAnd: return builder->CreateAnd(l, r, "andtmp");
  case FB::BitwiseOr:  return builder->CreateOr(l, r, "ortmp");
  case FB::BitwiseXor: return builder->CreateXor(l, r, "xortmp");
  case FB::ShiftLeft:  return builder->CreateShl(l, r, "shltmp");
  case FB::ShiftRight: return builder->CreateAShr(l, r, "ashrtmp");
  case FB::AnchorIn:   return anchorIn(expr);
  case FB::AnchorOut:  return anchorOut(expr);
  default:             return nullptr;
    // clang-format on
  }
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

void fysh::Program::print(const std::string &path) {
  if (path == "-") {
    for (const auto &fn : *this) {
      fn->print(llvm::outs());
    }
  } else {
    std::error_code ec;
    llvm::raw_fd_ostream outputFile(path.c_str(), ec);
    if (outputFile.error()) {
      std::cerr << "Error opening file " << path
                << " for writing: " << ec.message() << "\n";
      std::exit(1);
    } else {

      for (const auto &fn : *this) {
        fn->print(outputFile);
      }
    }
  }
  for (const auto &fn : *this) {
    fn->eraseFromParent();
  }
}

bool fysh::Program::empty() const { return this->size() == 0; }

void fysh::Program::add(llvm::Function *fn) { this->push_back(fn); }
