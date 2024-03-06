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
 * \file VybeChecker.cc
 */
#include <iostream>
#include <map>
#include <string>

class SymbolTable {
public:
  std::map<std::string, std::string> table; // variable name -> type

  void declareVariable(const std::string &name, const std::string &type) {
    if (table.find(name) != table.end()) {
      std::cerr << "Variable " << name << " is already declared.\n";
      return;
    }
    table[name] = type;
  }

  bool isDeclared(const std::string &name) {
    return table.find(name) != table.end();
  }

  std::string getType(const std::string &name) {
    if (isDeclared(name)) {
      return table[name];
    }
    return ""; // Return empty if not found
  }
};

class VybeChecker {
private:
  SymbolTable symbolTable;

public:
  void analyzeNode(const std::string &nodeType, const std::string &name,
                   const std::string &type = "") {
    if (nodeType == "VariableDeclaration") {
      symbolTable.declareVariable(name, type);
    } else if (nodeType == "VariableUsage") {
      if (!symbolTable.isDeclared(name)) {
        std::cerr << "Variable " << name << " used without declaration.\n";
      }
    }
    // Add more cases as needed
  }

  // Example usage: analyzeNode("VariableDeclaration", "x", "int");
  // Example usage: analyzeNode("VariableUsage", "x");
};

// int main() {
//   SemanticAnalyzer analyzer;
//
//   // Simulate parsing variable declaration
//   analyzer.analyzeNode("VariableDeclaration", "x", "int");
//
//   // Simulate using a variable
//   analyzer.analyzeNode("VariableUsage", "x"); // No error
//   analyzer.analyzeNode("VariableUsage", "y"); // This should show an error
//
//   return 0;
// }
