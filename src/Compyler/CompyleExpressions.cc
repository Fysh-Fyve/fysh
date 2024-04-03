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
 * \file CompyleExpressions.cc
 */
#include "Compyler.h"
#include "Variable.h"

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
        } else if constexpr (std::is_same_v<T, ast::FyshFloatLiteral>) {
          return llvm::ConstantFP::get(*context, llvm::APFloat(arg.num));
        } else if constexpr (std::is_same_v<T, ast::GrilledFysh>) {
          return grilledFysh();
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      *expr);
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

  llvm::Function *func;
  // Add some builtins
  // TODO: Maybe do a cleaner way?
  if (expr.callee == "get_seg") {
    func = getOrDefine(expr.callee, intTy(), Params{intTy()});
  } else if (expr.callee == "counter_read") {
    func = getOrDefine(expr.callee, intTy(), Params{});
  } else {
    func = getFunction(expr.callee);
  }
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
