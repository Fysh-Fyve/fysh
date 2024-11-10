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
 * \file Variable.h
 */
#ifndef FYSH_VARIABLE_H_
#define FYSH_VARIABLE_H_

#include "../Parser/AST/AST.h"
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instructions.h>
#include <variant>

namespace fysh {
struct Undefined {};

struct Variable : std::variant<llvm::GlobalVariable *, llvm::AllocaInst *,
                               llvm::Argument *, Undefined> {
  inline bool operator!() { return std::holds_alternative<Undefined>(*this); }

  constexpr llvm::Type *type() {
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

}; // namespace fysh

#endif // !FYSH_VARIABLE_H_
