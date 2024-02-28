#include "Compyler.h"
#include "AST.h"

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
      builder{std::make_unique<llvm::IRBuilder<>>(*context)} {}

llvm::AllocaInst *
fysh::Compyler::createEntryBlockAlloca(llvm::Function *TheFunction,
                                       const std::string_view &name) {
  llvm::IRBuilder<> builder{&TheFunction->getEntryBlock(),
                            TheFunction->getEntryBlock().begin()};
  return builder.CreateAlloca(llvm::Type::getInt32Ty(*context), nullptr, name);
}

llvm::Function *
fysh::Compyler::compyle(std::vector<fysh::ast::FyshStmt> program) {
  // int() function type
  llvm::FunctionType *ft = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*context), std::vector<llvm::Type *>(), false);
  llvm::Function *prototype = llvm::Function::Create(
      ft, llvm::Function::ExternalLinkage, "main", module.get());

  llvm::BasicBlock *bb = llvm::BasicBlock::Create(*context, "entry", prototype);
  builder->SetInsertPoint(bb);

  llvm::Value *retVal;

  for (auto &stmt : program) {
    fysh::Emit emit = std::visit(
        [this, prototype](auto &&arg) -> fysh::Emit {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, ast::Error>) {
            return arg;
          } else if constexpr (std::is_same_v<T, ast::FyshExpr>) {
            return compyle(&arg);
          } else if constexpr (std::is_same_v<T, ast::FyshIncrementStmt>) {
            return nullptr;
          } else if constexpr (std::is_same_v<T, ast::FyshDecrementStmt>) {
            return nullptr;
          } else if constexpr (std::is_same_v<T, ast::FyshAssignmentStmt>) {
            // Only handle assignments to identifiers for now
            if (auto ident = std::get_if<ast::FyshIdentifier>(&arg.left)) {
              if (namedValues.find(ident->name) == namedValues.end()) {
                namedValues[ident->name] =
                    createEntryBlockAlloca(prototype, ident->name);
              }
              auto alloca{namedValues[ident->name]};
              auto val{compyle(&arg.right)};
              if (auto expr = std::get_if<llvm::Value *>(&val)) {
                builder->CreateStore(*expr, alloca);
              }
              return nullptr;
            } else {
              return ast::Error{"assigning to non-variable"};
            }
          } else if constexpr (std::is_same_v<T, ast::FyshBlock>) {
            return nullptr;
          } else if constexpr (std::is_same_v<T, ast::FyshLoopStmt>) {
            return nullptr;
          } else if constexpr (std::is_same_v<T, ast::FyshIfStmt>) {
            return nullptr;
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        stmt);

    if (auto error = std::get_if<ast::Error>(&emit)) {
      std::cerr << error << std::endl;
      // Error reading body, remove function.
      prototype->eraseFromParent();
      return nullptr;
    } else if (auto expr = std::get_if<llvm::Value *>(&emit)) {
      retVal = *expr;
    }
  }
  if (!retVal) {
    // Error reading body, remove function.
    prototype->eraseFromParent();
    return nullptr;
  }

  // Finish off the function.
  builder->CreateRet(retVal);

  // Validate the generated code, checking for consistency.
  llvm::verifyFunction(*prototype);

  return prototype;
}

fysh::Emit fysh::Compyler::compyle(fysh::ast::FyshExpr *expr) {
  if (expr == nullptr) {
    return nullptr;
  }
  return std::visit(
      [this](auto &&arg) -> fysh::Emit {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, ast::Error>) {
          return arg;
        } else if constexpr (std::is_same_v<T, Box<ast::FyshBinaryExpr>>) {
          auto binOp = arg.getraw();
          auto left = compyle(&binOp.left);
          auto right = compyle(&binOp.right);
          if (auto err = std::get_if<ast::Error>(&left)) {
            return *err;
          }
          if (auto err = std::get_if<ast::Error>(&right)) {
            return *err;
          }
          auto leftVal = std::get<llvm::Value *>(left);
          auto rightVal = std::get<llvm::Value *>(right);
          if (binOp.op == ast::FyshBinary::Add) {
            return builder->CreateAdd(leftVal, rightVal, "addtmp");
          } else if (binOp.op == ast::FyshBinary::Mul) {
            return builder->CreateMul(leftVal, rightVal, "multmp");
          } else if (binOp.op == ast::FyshBinary::Div) {
            return builder->CreateMul(leftVal, rightVal, "divtmp");
          }
          // TODO: Do other operations
          return nullptr;
        } else if constexpr (std::is_same_v<T, Box<ast::FyshUnaryExpr>>) {
          auto unaryOp = arg.getraw();
          auto emit = compyle(&unaryOp.expr);
          if (auto err = std::get_if<ast::Error>(&emit)) {
            return *err;
          }
          if (unaryOp.op == ast::FyshUnary::Neg) {
            return builder->CreateNeg(std::get<llvm::Value *>(emit));
          }
          return nullptr;
        } else if constexpr (std::is_same_v<T, ast::FyshIdentifier>) {
          if (namedValues.find(arg.name) == namedValues.end()) {
            return ast::Error{"unknown variable"};
          }
          auto alloc{namedValues[arg.name]};
          return builder->CreateLoad(alloc->getAllocatedType(), alloc,
                                     arg.name);
        } else if constexpr (std::is_same_v<T, ast::FyshLiteral>) {
          return llvm::ConstantInt::get(*context, llvm::APInt(32, arg.num));
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      *expr);
}
