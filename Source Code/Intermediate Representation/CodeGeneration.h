#pragma once

#include "../Parser/AST.h"

#include <sstream>
#include <unordered_map>

// Create a symbol table unordered_map (source code variables (number, word, node) to cpp code variables (int, string, double)

const std::unordered_map<std::string, std::string> typeMap = { //We should add boolean handling to the map soon
    { "number", "int" },
    { "decimal", "double"},
    { "word", "std::string" },
    { "bool", "bool" },
};

std::string mapType(const std::string& type);
std::string generateExpression(const Expression* expr);
std::string generateStatement(const Statement* statement, int indent = 0);
std::string generateBlock(const std::vector<Statement*>& block, int indent);
std::string generateCondition(const Expression* expr);

std::string generateIf(const IfStatement* node, int indent, bool isElseIf = false);

std::string GenerateCode(const Program* program);