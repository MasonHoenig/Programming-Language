#include "../Parser/AST.h"

#include <sstream>
#include <unordered_map>

// Create a symbol table unordered_map (source code variables (number, word, node) to cpp code variables (int, string, double)

const std::unordered_map<std::string, std::string> typeMap = {
    { "number", "int" },
    { "decimal", "double"},
    { "word", "std::string" },
    // bool translates directly
};

std::string mapType(const std::string type);
std::string variableDeclaration(const std::string& varType, const std::string& identifier, const Expression* initializer);