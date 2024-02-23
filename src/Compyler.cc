#include "Compyler.h"

#include <llvm/ADT/APInt.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <variant>

fysh::Compyler::Compyler()
    : context{std::make_unique<llvm::LLVMContext>()},
      module{std::make_unique<llvm::Module>("fysh", *context)},
      builder{std::make_unique<llvm::IRBuilder<>>(*context)} {}

llvm::Function *
fysh::Compyler::compyle(std::vector<fysh::ast::FyshStmt> program) {
  // int() function type
  llvm::FunctionType *ft = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*context), std::vector<llvm::Type *>(), false);
  llvm::Function *prototype = llvm::Function::Create(
      ft, llvm::Function::ExternalLinkage, "main", module.get());

  llvm::BasicBlock *bb = llvm::BasicBlock::Create(*context, "entry", prototype);
  builder->SetInsertPoint(bb);

  // assume that there is only one expression for now?
  if (auto expr = std::get_if<ast::FyshExpr>(&program[0])) {
    if (llvm::Value *retVal = compyle(expr)) {
      // Finish off the function.
      builder->CreateRet(retVal);

      // Validate the generated code, checking for consistency.
      llvm::verifyFunction(*prototype);

      return prototype;
    }
  }

  // Error reading body, remove function.
  prototype->eraseFromParent();
  return nullptr;
}

llvm::Value *fysh::Compyler::compyle(fysh::ast::FyshExpr *expr) {
  if (expr == nullptr) {
    return nullptr;
  }
  return std::visit(
      [this](auto &&arg) -> llvm::Value * {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, ast::Error>) {
          return nullptr;
        } else if constexpr (std::is_same_v<T, Box<ast::FyshBinaryExpr>>) {
          auto binExpr = arg.getraw();
          if (binExpr.op == ast::FyshBinary::Add) {
            auto left = compyle(&binExpr.left);
            auto right = compyle(&binExpr.left);
            if (!left || !right) {
              return nullptr;
            }
            return builder->CreateAdd(left, right, "addtmp");
          }
          // TODO: Do other operations
          return nullptr;
        } else if constexpr (std::is_same_v<T, Box<ast::FyshUnaryExpr>>) {
          return nullptr;
        } else if constexpr (std::is_same_v<T, ast::FyshIdentifier>) {
          return nullptr;
        } else if constexpr (std::is_same_v<T, ast::FyshLiteral>) {
          return llvm::ConstantInt::get(*context, llvm::APInt(32, arg.num));
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      *expr);
}
