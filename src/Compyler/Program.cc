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
 * \file Program.cc
 */
#include "Program.h"
#include <iostream>

void fysh::Program::print(const std::string &path) {
  if (path == "-") {
    for (const auto &fn : *this) {
      fn->print(llvm::outs());
    }
  } else {
    std::error_code ec;
    llvm::raw_fd_ostream outputFile{path.c_str(), ec};
    if (outputFile.error()) {
      std::cerr << "Error opening file " << path
                << " for writing: " << ec.message() << "\n";
      std::exit(1);
    } else {

      for (const auto &fn : *this) {
        fn->print(outputFile);
      }
    }
  }
  for (const auto &fn : *this) {
    fn->eraseFromParent();
  }
}

bool fysh::Program::empty() const { return this->size() == 0; }

void fysh::Program::add(llvm::Function *fn) { this->push_back(fn); }
