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
#include "../Parser/AST/AST.h"

#include <llvm/ADT/APInt.h>
#include <llvm/IR/Argument.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <memory>
#include <unordered_map>
#include <variant>

using Params = std::vector<llvm::Type *>;

fysh::Compyler::Compyler(std::string filename)
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
  module->setSourceFileName(filename.substr(filename.find_last_of("/\\") + 1));

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

llvm::Function *fysh::Compyler::define(const std::string_view &name,
                                       llvm::Type *returnType,
                                       std::vector<llvm::Type *> params) {
  llvm::Function *fn{llvm::Function::Create(
      llvm::FunctionType::get(returnType, params, false),
      llvm::Function::ExternalLinkage, name, module.get())};
  subs[name] = fn;
  return fn;
};

llvm::Function *fysh::Compyler::getFunction(const std::string_view &name) {
  if (subs.find(name) == subs.end())
    return nullptr;
  return subs[name];
}

llvm::Function *fysh::Compyler::getOrDefine(const std::string_view &name,
                                            llvm::Type *returnType,
                                            std::vector<llvm::Type *> params) {
  llvm::Function *func{getFunction(name)};
  if (!func) {
    func = define(name, returnType, params);
  }
  return func;
};

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

fysh::Emit fysh::Compyler::anchorIn(const fysh::ast::FyshBinaryExpr &expr) {
  fysh::Emit pin{expression(&expr.left)};
  if (isError(pin)) {
    return pin;
  }
  if (const ast::FyshIdentifier *ident =
          std::get_if<ast::FyshIdentifier>(&expr.right)) {
    fysh::Variable variable{resolveVariable(ident->name, Definition::LOCAL)};
    // int fysh_gpio_read(int pin)
    llvm::Function *func{
        getOrDefine("fysh_gpio_read", intTy(), Params{intTy()})};
    llvm::Value *retVal{
        builder->CreateCall(func->getFunctionType(), func,
                            std::vector<llvm::Value *>{unwrap(pin)})};
    builder->CreateStore(retVal, variable.val());
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
  // void fysh_gpio_write(int pin, int value)
  llvm::Function *func{
      getOrDefine("fysh_gpio_write", voidTy(), Params{intTy(), intTy()})};
  return builder->CreateCall(
      func->getFunctionType(), func,
      std::vector<llvm::Value *>{unwrap(pin), unwrap(value)});
}

fysh::Variable
fysh::Compyler::resolveVariable(const std::string_view &name,
                                Definition define = Definition::NONE) {
  // Try local scope first
  if (locals.find(name) != locals.end()) {
    return {locals[name]};
  }

  // Try then args
  if (args.find(name) != args.end()) {
    return {args[name]};
  }

  // Then global scope
  if (globals.find(name) != globals.end()) {
    return {globals[name]};
  }

  // Then try to define it
  switch (define) {
  case Definition::LOCAL: {
    locals[name] = builder->CreateAlloca(intTy(), nullptr, name);
    return {locals[name]};
  }
  case Definition::GLOBAL: {
    module->getOrInsertGlobal(name, intTy());
    globals[name] = module->getNamedGlobal(name);
    globals[name]->setLinkage(llvm::GlobalValue::PrivateLinkage);
    globals[name]->setInitializer(builder->getInt32(0));
    return {globals[name]};
  }
  case Definition::NONE: {
    return {fysh::Undefined{}};
  }
  }
}

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
          return block(arg);
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

static void print(llvm::Module *m, const std::string &path) {
  if (path == "-") {
    llvm::outs() << *m;
  } else {
    std::error_code ec;
    llvm::raw_fd_ostream outputFile{path.c_str(), ec};
    if (outputFile.error()) {
      llvm::errs() << "Error opening file " << path
                   << " for writing: " << ec.message() << "\n";
      std::exit(1);
    } else {
      outputFile << m;
    }
  }
}

std::optional<fysh::ast::Error>
fysh::Compyler::subroutine(const fysh::ast::SUBroutine &sub, bool noOpt) {
  Params params;
  for (const auto &_ : sub.parameters) {
    params.push_back(intTy());
  }
  llvm::Function *subPrototype{define(sub.name, intTy(), params)};
  llvm::BasicBlock *bb{
      llvm::BasicBlock::Create(*context, "entry", subPrototype)};
  builder->SetInsertPoint(bb);

  args.clear();
  locals.clear();
  size_t idx = 0;
  for (auto &arg : subPrototype->args()) {
    arg.setName(sub.parameters[idx++]);
    args[arg.getName()] = &arg;
  }

  Emit emit;
  for (const auto &s : sub.body) {
    Emit e{statement(s)};
    if (isError(e)) {
      // Something went wrong!
      subPrototype->eraseFromParent();
      return std::get<ast::Error>(e);
    }
    if (llvm::Value *expr = unwrap(e)) {
      emit = expr;
    }
  }

  if (llvm::Value *expr = unwrap(emit)) {
    // Finish off the function.
    builder->CreateRet(expr);
  } else {
    // Implicitly return 0
    builder->CreateRet(builder->getInt32(0));
  }

  // Validate the generated code, checking for consistency.
  llvm::verifyFunction(*subPrototype);

  if (!noOpt) {
    fpm->run(*subPrototype, *fam);
  }

  return {};
}

void fysh::Compyler::compyle(const fysh::ast::FyshProgram &ast,
                             fysh::Options opts) {
  std::vector<ast::FyshStmt> statements;
  std::vector<ast::SUBroutine> subs;
  for (const auto &declarations : ast) {
    std::optional<ast::Error> error{std::visit(
        [&](auto &&arg) -> std::optional<ast::Error> {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, ast::Error>) {
            return arg;
          } else if constexpr (std::is_same_v<T, ast::FyshStmt>) {
            statements.push_back(arg);
            return {};
          } else if constexpr (std::is_same_v<T, ast::SUBroutine>) {
            subs.push_back(arg);
            return {};
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        declarations)};
    if (error.has_value()) {
      llvm::errs() << error.value().getraw() << "\n";
      // Something went wrong!
      return;
    }
  }

  for (const auto &s : statements) {
    auto var{std::visit(
        [&](auto &&arg) -> std::optional<std::string_view> {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, ast::FyshAssignmentStmt>) {
            if (auto *ident = std::get_if<ast::FyshIdentifier>(&arg.left)) {
              return ident->name;
            }
          } else if constexpr (std::is_same_v<T, ast::FyshAnchorStmt>) {
            if (arg.op == ast::FyshBinary::AnchorIn) {
              if (auto *ident = std::get_if<ast::FyshIdentifier>(&arg.right)) {
                return ident->name;
              }
            }
          }
          return {};
        },
        s)};
    if (var) {
      resolveVariable(var.value(), Definition::GLOBAL);
    }
  }

  for (const auto &sub : subs) {
    auto error{subroutine(sub, opts.noOpt)};
    if (error.has_value()) {
      llvm::errs() << error.value().getraw() << "\n";
      return;
    }
  }

  ast::SUBroutine main{"main", {}, statements};
  auto error{subroutine(main, opts.noOpt)};
  if (error.has_value()) {
    llvm::errs() << error.value().getraw() << "\n";
    return;
  }

  print(module.get(), opts.outputFilename);
}

fysh::Emit fysh::Compyler::call(const fysh::ast::FyshCallExpr &expr) {
  std::vector<llvm::Value *> argValues;
  argValues.reserve(expr.args.size());
  for (const auto &arg : expr.args) {
    Emit e{expression(&arg)};
    if (isError(e)) {
      return e;
    }
    argValues.push_back(unwrap(e));
  }

  llvm::Function *func{getFunction(expr.callee)};
  if (!func) {
    std::string str;
    llvm::raw_string_ostream ss{str};
    ss << "subroutine `" << expr.callee << "` does not exist";
    return ast::Error{ss.str()};
  }

  llvm::Value *retVal{
      builder->CreateCall(func->getFunctionType(), func, argValues)};
  return (expr.negate) ? builder->CreateNeg(retVal) : retVal;
}

fysh::Emit fysh::Compyler::unary(const fysh::ast::FyshUnaryExpr &expr) {
  Emit emit{expression(&expr.expr)};
  if (isError(emit)) {
    return emit;
  }
  if (expr.op == ast::FyshUnary::Neg) {
    return builder->CreateNeg(unwrap(emit));
  }
  return nullptr;
}

fysh::Emit fysh::Compyler::binary(const fysh::ast::FyshBinaryExpr &expr) {
  fysh::Emit left{expression(&expr.left)};
  fysh::Emit right{expression(&expr.right)};
  if (isError(left)) {
    return left;
  }
  if (isError(right)) {
    return right;
  }
  llvm::Value *l{unwrap(left)};
  llvm::Value *r{unwrap(right)};

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
  Variable variable{resolveVariable(expr.name)};
  if (!variable) {
    return ast::Error{"unknown variable"};
  }
  // You cannot load the argument because it's a plain value
  // TODO: Create a new local variable if one attempts to "store" to an argument
  // This would also apply to the increment/decrement stuff
  if (std::holds_alternative<llvm::Argument *>(variable)) {
    return variable.val();
  } else {
    return builder->CreateLoad(variable.type(), variable.val(), expr.name);
  }
}

fysh::Emit fysh::Compyler::grilledFysh() {
  llvm::Function *func{getOrDefine("fysh_grilled", intTy(), Params{})};
  return builder->CreateCall(func->getFunctionType(), func,
                             std::vector<llvm::Value *>());
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
        } else if constexpr (std::is_same_v<T, Box<ast::FyshCallExpr>>) {
          return call(arg.getraw());
        } else if constexpr (std::is_same_v<T, ast::FyshIdentifier>) {
          return identifier(arg);
        } else if constexpr (std::is_same_v<T, ast::FyshLiteral>) {
          return builder->getInt32(arg.num);
        } else if constexpr (std::is_same_v<T, ast::GrilledFysh>) {
          return grilledFysh();
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      *expr);
}

llvm::Value *fysh::unwrap(const Emit &v) { return std::get<llvm::Value *>(v); }
