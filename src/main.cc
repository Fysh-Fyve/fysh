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
 * \file main.cc
 */
#include "AST/AST.h"
#include "Compyler/Compyler.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include <fstream>
#include <iostream>
#include <llvm/Support/raw_ostream.h>
#include <sstream>

void compyle(std::istream &stream) {
  std::stringstream ss;
  ss << stream.rdbuf();
  std::string source{ss.str()};
  fysh::FyshLexer lexer{source.data()};
  fysh::FyshParser parser{lexer};
  fysh::ast::FyshBlock program{parser.parseProgram()};

  if (program.size() == 1) {
    if (const fysh::ast::Error *err =
            std::get_if<fysh::ast::Error>(&program[0])) {
      std::cerr << "Error: " << err->getraw() << std::endl;
      return;
    }
  }

  fysh::Compyler cumpyler;
  llvm::Function *fn{cumpyler.compyle(program)};
  if (fn == nullptr) {
    std::cerr << "error compyling?" << std::endl;
  } else {
    fn->print(llvm::outs());
    fn->eraseFromParent();
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    compyle(std::cin);
  } else {
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
      std::cerr << "Error opening file " << argv[1] << " for reading\n";
      return 1;
    }
    compyle(inputFile);
  }
  return 0;
}
