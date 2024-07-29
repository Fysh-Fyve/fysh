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
 * \file babel-fysh.cc
 */

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include <iostream>

int main(int argc, char *argv[]) {
  for (std::string line; std::getline(std::cin, line);) {
    fysh::FyshParser parser{fysh::FyshLexer{line.data()}};
    auto program{parser.parseProgram()};
    auto err{program.getError()};
    if (err) {
      std::cout << err->getraw() << "\n";
    } else {
      // TODO: Eval program here
      std::cout << std::to_string(program);
    }
  }
  std::cout << "\n";
}
