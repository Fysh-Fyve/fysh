#include "Compyler.h"
#include "AST.h"

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
          auto binOp = arg.getraw();
          auto left = compyle(&binOp.left);
          auto right = compyle(&binOp.right);
          if (!left || !right) {
            return nullptr;
          }
          if (binOp.op == ast::FyshBinary::Add) {
            return builder->CreateAdd(left, right, "addtmp");
          } else if (binOp.op == ast::FyshBinary::Mul) {
            return builder->CreateMul(left, right, "multmp");
          } else if (binOp.op == ast::FyshBinary::Div) {
            return builder->CreateMul(left, right, "divtmp");
          }
          // TODO: Do other operations
          return nullptr;
        } else if constexpr (std::is_same_v<T, Box<ast::FyshUnaryExpr>>) {
          auto unaryOp = arg.getraw();
          auto expr = compyle(&unaryOp.expr);
          if (!expr) {
            return nullptr;
          }
          if (unaryOp.op == ast::FyshUnary::Neg) {
            return builder->CreateNeg(expr);
          }
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
