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

fysh::Emit fysh::Compyler::compyleLoop(const fysh::ast::FyshLoopStmt &loop,
                                       llvm::Function *function) {
  llvm::Function *parent{builder->GetInsertBlock()->getParent()};
  llvm::BasicBlock *conditionBlock{builder->GetInsertBlock()};
  Emit condEmit{compyleExpr(&loop.condition)};
  if (std::holds_alternative<ast::Error>(condEmit)) {
    return condEmit;
  }
  llvm::Value *loopCond{std::get<llvm::Value *>(condEmit)};
  llvm::BasicBlock *loopBlock{
      llvm::BasicBlock::Create(*context, "loop", parent)};
  builder->SetInsertPoint(loopBlock);
  return nullptr;
}

fysh::Emit fysh::Compyler::handleAssignment(const fysh::ast::FyshStmt &stmt,
                                            llvm::Function *function) {
  // Assuming the statement is an assignment
  // Placeholder logic, replace with actual assignment handling
  return fysh::Emit{}; // Adjust based on your Emit type
}

fysh::Emit fysh::Compyler::handleIncDecStmt(const fysh::ast::FyshStmt &stmt,
                                            llvm::Function *function) {
  // Assuming the statement is either an increment or decrement statement
  // Placeholder logic, replace with actual increment/decrement handling
  return fysh::Emit{}; // Adjust based on your Emit type
}

fysh::Emit fysh::Compyler::handleStatement(const fysh::ast::FyshStmt &stmt,
                                           llvm::Function *function) {
  // Example handling based on the type of statement
  // This needs to be replaced with actual handling logic
  if (auto expr = std::get_if<fysh::ast::FyshExpr>(&stmt)) {
    return compyleExpr(expr);
  } else if (auto block = std::get_if<fysh::ast::FyshBlock>(&stmt)) {
    return compyleBlock(*block, function);
  }
  // Add handling for other statement types (loops, if statements, etc.)

  return fysh::Emit{}; // Placeholder return, adjust based on your Emit type
}

fysh::Emit
fysh::Compyler::compyleBlock(const std::vector<fysh::ast::FyshStmt> &program,
                             llvm::Function *function) {
  llvm::Value *retVal = nullptr; // Initialize retVal explicitly

  for (auto &stmt : program) {
    fysh::Emit emit = std::visit(
        [this, function](auto &&arg) -> fysh::Emit {
          using T = std::decay_t<decltype(arg)>;

          if constexpr (std::is_same_v<T, ast::Error>) {
            return arg;
          } else if constexpr (std::is_same_v<T, ast::FyshExpr> ||
                               std::is_same_v<T, ast::FyshBlock> ||
                               std::is_same_v<T, ast::FyshLoopStmt> ||
                               std::is_same_v<T, ast::FyshIfStmt>) {
            // Handle expressions, blocks, loops, and if statements directly.
            return handleStatement(
                arg, function); // Implement handleStatement for these types.
          } else if constexpr (std::is_same_v<T, ast::FyshIncrementStmt> ||
                               std::is_same_v<T, ast::FyshDecrementStmt>) {
            // Handle increments and decrements.
            //// Implement handleIncDecStmt.
            return handleIncDecStmt(arg, function);
          } else if constexpr (std::is_same_v<T, ast::FyshAssignmentStmt>) {
            // Handle assignment statements.
            //// Implement handleAssignment.
            return handleAssignment(arg, function);
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        stmt);

    if (auto error = std::get_if<ast::Error>(&emit)) {
      return *error;
    }
    if (auto expr = std::get_if<llvm::Value *>(&emit)) {
      retVal = *expr;
    }
  }

  // Return the last expression's value or nullptr if no expressions were
  // executed.
  return retVal;
}

llvm::Function *
fysh::Compyler::compyle(const std::vector<fysh::ast::FyshStmt> &program) {
  // int() function type
  llvm::FunctionType *ft = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*context), std::vector<llvm::Type *>(), false);
  llvm::Function *prototype = llvm::Function::Create(
      ft, llvm::Function::ExternalLinkage, "main", module.get());

  llvm::BasicBlock *bb = llvm::BasicBlock::Create(*context, "entry", prototype);
  builder->SetInsertPoint(bb);

  Emit emit = compyleBlock(program, prototype);

  if (auto expr = std::get_if<llvm::Value *>(&emit)) {
    // Finish off the function.
    builder->CreateRet(*expr);
    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*prototype);

    return prototype;
  } else if (auto error = std::get_if<ast::Error>(&emit)) {
    std::cerr << error << std::endl;
  }

  // Something went wrong!
  prototype->eraseFromParent();
  return nullptr;
}

fysh::Emit fysh::Compyler::compyleExpr(const fysh::ast::FyshExpr *expr) {
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
          auto left = compyleExpr(&binOp.left);
          auto right = compyleExpr(&binOp.right);
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
          } else if (binOp.op == ast::FyshBinary::GT) {
            return builder->CreateICmpUGT(leftVal, rightVal, "gttmp");
          }
          // TODO: Do other operations
          return nullptr;
        } else if constexpr (std::is_same_v<T, Box<ast::FyshUnaryExpr>>) {
          auto unaryOp = arg.getraw();
          auto emit = compyleExpr(&unaryOp.expr);
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
