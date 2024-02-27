#include <iostream>
#include <map>
#include <string>

class SymbolTable {
public:
    std::map<std::string, std::string> table; // variable name -> type

    void declareVariable(const std::string& name, const std::string& type) {
        if (table.find(name) != table.end()) {
            std::cerr << "Variable " << name << " is already declared.\n";
            return;
        }
        table[name] = type;
    }

    bool isDeclared(const std::string& name) {
        return table.find(name) != table.end();
    }

    std::string getType(const std::string& name) {
        if (isDeclared(name)) {
            return table[name];
        }
        return ""; // Return empty if not found
    }
};

class SemanticAnalyzer {
private:
    SymbolTable symbolTable;

public:
    void analyzeNode(const std::string& nodeType, const std::string& name, const std::string& type = "") {
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

int main() {
    SemanticAnalyzer analyzer;

    // Simulate parsing variable declaration
    analyzer.analyzeNode("VariableDeclaration", "x", "int");

    // Simulate using a variable
    analyzer.analyzeNode("VariableUsage", "x"); // No error
    analyzer.analyzeNode("VariableUsage", "y"); // This should show an error

    return 0;
}
