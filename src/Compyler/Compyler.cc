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
#include "Variable.h"

#include <llvm-18/llvm/PassInfo.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Argument.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/StandardInstrumentations.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Scalar/Reassociate.h>
#include <llvm/Transforms/Scalar/SimplifyCFG.h>
#include <memory>
#include <unordered_map>
#include <variant>

template <typename T> constexpr auto make = std::make_unique<T>;

fysh::Compyler::Compyler(std::string filename)
    : context{make<llvm::LLVMContext>()},
      module{std::make_unique<llvm::Module>("fysh", *context)},
      builder{std::make_unique<llvm::IRBuilder<>>(*context)},
      fpm{make<llvm::FunctionPassManager>()},
      lam{make<llvm::LoopAnalysisManager>()},
      fam{make<llvm::FunctionAnalysisManager>()},
      cgam{make<llvm::CGSCCAnalysisManager>()},
      mam{make<llvm::ModuleAnalysisManager>()},
      pic{make<llvm::PassInstrumentationCallbacks>()},
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

inline void print(llvm::Module *m, const std::string &path) {
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
      outputFile << *m;
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
          }
          return {};
        },
        s)};
    if (var) {
      resolveVariable(var.value(), Definition::GLOBAL);
    }
  }
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

  defineGlobals(statements);

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
