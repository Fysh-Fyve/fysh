#include "Compyler.h"

#include <memory>

fysh::Compyler::Compyler()
    : context{std::make_unique<llvm::LLVMContext>()},
      module{std::make_unique<llvm::Module>("fysh", *context)},
      builder{std::make_unique<llvm::IRBuilder<>>(*context)} {}

llvm::Value *fysh::Compyler::compyle(std::vector<fysh::ast::FyshStmt> program) {
  return nullptr;
}
