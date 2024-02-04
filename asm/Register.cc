/**
 * Copyright (C) 2024 Charles Ancheta
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
 * \file Register.cc
 */
#include "Register.h"
#include <string_view>
#include <unordered_map>

int8_t fasm::lookupRegister(std::string_view reg) {
  static std::unordered_map<std::string_view, int8_t> registers = {
      {"x0", 0},
      {"x1", 1},
      {"x2", 2},
      {"x3", 3},
      {"x4", 4},
      {"x5", 5},
      {"x6", 6},
      {"x7", 7},
      {"x8", 8},
      {"x9", 9},
      {"x10", 10},
      {"x11", 11},
      {"x12", 12},
      {"x13", 13},
      {"x14", 14},
      {"x15", 15},
      {"x16", 16},
      {"x17", 17},
      {"x18", 18},
      {"x19", 19},
      {"x20", 20},
      {"x21", 21},
      {"x22", 22},
      {"x23", 23},
      {"x24", 24},
      {"x25", 25},
      {"x26", 26},
      {"x27", 27},
      {"x28", 28},
      {"x29", 29},
      {"x30", 30},
      {"x31", 31},
      /* RISC-V ABI */
      // https://en.wikichip.org/wiki/risc-v/registers
      {"zero", 0}, // hardwired zero
      {"ra", 1},   // return address
      {"sp", 2},   // stack pointer
      {"gp", 3},   // global pointer
      {"tp", 4},   // thread pointer
      {"t0", 5},   // temporary register 0
      {"t1", 6},   // temporary register 1
      {"t2", 7},   // temporary register 2
      {"s0", 8},   // saved register 0
      {"fp", 8},   // frame pointer
      {"s1", 9},   // saved register 1
      {"a0", 10},  // function argument 0 / return value 0
      {"a1", 11},  // function argument 1 / return value 1
      {"a2", 12},  // function argument 2
      {"a3", 13},  // function argument 3
      {"a4", 14},  // function argument 4
      {"a5", 15},  // function argument 5
      {"a6", 16},  // function argument 6
      {"a7", 17},  // function argument 7
      {"s2", 18},  // saved register 2
      {"s3", 19},  // saved register 3
      {"s4", 20},  // saved register 4
      {"s5", 21},  // saved register 5
      {"s6", 22},  // saved register 6
      {"s7", 23},  // saved register 7
      {"s8", 24},  // saved register 8
      {"s9", 25},  // saved register 9
      {"s10", 26}, // saved register 10
      {"s11", 27}, // saved register 11
      {"t3", 28},  // temporary register 3
      {"t4", 29},  // temporary register 4
      {"t5", 30},  // temporary register 5
      {"t6", 31},  // temporary register 6
  };
  auto it = registers.find(reg);
  if (it != registers.end()) {
    return it->second;
  } else {
    return -1;
  }
}
