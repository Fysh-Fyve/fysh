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
#include "Compyler.h"
#include "Lexer.h"
#include "Parser.h"
#include <llvm-18/llvm/Support/raw_ostream.h>

int main() {
  fysh::FyshLexer lexer{"><{{({(o> ><{{({(o> ~"};
  fysh::FyshParser parser{lexer};
  auto program{parser.parseProgram()};
  fysh::Compyler cumpyler;

  auto fn{cumpyler.compyle(program)};

  fn->print(llvm::outs());
  fn->eraseFromParent();

  return 0;
}
