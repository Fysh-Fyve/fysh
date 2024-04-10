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
 * \file Symbols.cc
 */
#include "Compyler.h"
#include "Variable.h"

#include <algorithm>
#include <string>

llvm::Function *fysh::Compyler::define(const std::string_view &name,
                                       llvm::Type *returnType,
                                       std::vector<llvm::Type *> params) {
  std::string s{name};
  std::replace(s.begin(), s.end(), ' ', '_');
  llvm::Function *fn{
      llvm::Function::Create(llvm::FunctionType::get(returnType, params, false),
                             llvm::Function::ExternalLinkage, s, module.get())};
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

fysh::Variable fysh::Compyler::resolveVariable(const std::string_view &name,
                                               Definition define) {
#define FIND_IN(m)                                                             \
  if (m.find(name) != m.end()) {                                               \
    return {m[name]};                                                          \
  }
  // Try local scope first
  FIND_IN(locals);
  // Try then args
  FIND_IN(args);
  // Then global scope
  FIND_IN(globals);
#undef FIND_IN

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
  default:
    assert(false);
    // should never be here
    return {fysh::Undefined{}};
  }
}

void fysh::Compyler::defineGlobals(
    const std::vector<ast::FyshStmt> &statements) {
  for (const auto &s : statements) {
    auto var{std::visit(
        [](auto &&arg) -> std::optional<std::string_view> {
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
          } else if constexpr (std::is_same_v<T, ast::FyshExpr>) {
            // If it's a single fysh variable it's the same as setting it to
            // zero
            if (auto *ident = std::get_if<ast::FyshIdentifier>(&arg)) {
              return ident->name;
            }
          }

          return {};
        },
        s)};
    if (var) {
      resolveVariable(var.value(), Definition::GLOBAL);
    }
  }
}
