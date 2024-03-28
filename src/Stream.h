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
 * \file Stream.h
 */
#ifndef FYSH_STREAM_H_
#define FYSH_STREAM_H_

#ifdef __llvm__
#include <llvm/Support/raw_ostream.h>
#define OUTS llvm::outs()
#define ERRS llvm::errs()
#else
#include <iostream>
#include <ostream>
#include <sstream>
#define OUTS std::cout
#define ERRS std::cerr
#endif // __llvm__

namespace fysh {
#ifdef __llvm__
using Stream = llvm::raw_ostream;
using StringStream = llvm::raw_string_ostream;
#else
using Stream = std::ostream;
using StringStream = std::ostringstream;
#endif // __llvm__
};     // namespace fysh

#endif // !FYSH_STREAM_H_
