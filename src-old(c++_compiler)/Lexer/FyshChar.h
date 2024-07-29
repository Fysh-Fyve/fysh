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
 * \file FyshChar.h
 */
#ifndef FYSH_CHAR_H_
#define FYSH_CHAR_H_

#include <string>
#include <string_view>
#include <variant>

namespace fysh {
struct FyshChar : public std::variant<const char *, std::string_view> {
  inline bool operator==(const char &x) const {
    return std::holds_alternative<const char *>(*this) &&
           *std::get<const char *>(*this) == x;
  }
  inline bool operator==(const char *x) const {
    return std::holds_alternative<std::string_view>(*this) &&
           std::get<std::string_view>(*this) == x;
  }
};

}; // namespace fysh

namespace std {
inline string to_string(const fysh::FyshChar &f) {
  if (std::holds_alternative<const char *>(f)) {
    return {*get<const char *>(f)};
  } else {
    return string(get<std::string_view>(f));
  }
}
}; // namespace std

#endif // !FYSH_CHAR_H_
