#include "CodeGeneration.h"

#include <iostream>

// Recursively iterate through AST (A lot of this can probably be taken from the current IR logic)
//
// On each iteration:
//	Check the type (isVariableDecl, isArithmetic, isBooleanExpr, etc.)
//	Execute code generation
//	Write output to output.cpp line by line

std::string mapType(const std::string& type) {
    auto it = typeMap.find(type);
    if (it == typeMap.end())
        throw std::runtime_error("Unknown type: " + type);
    return it->second;
}

// Takes Expression* and figures out what concrete type it is
std::string generateExpression(const Expression* expr) {
    if (auto* num = dynamic_cast<const NumberLiteral*>(expr))
        return num->value;

    if (auto* str = dynamic_cast<const StringLiteral*>(expr))
        return "\"" + str->value + "\"";

    if (auto* id = dynamic_cast<const Identifier*>(expr))
        return id->name;

    if (auto* binaryExpr = dynamic_cast<const BinaryExpression*>(expr)) {
        return "(" + generateExpression(binaryExpr->left) + " " + binaryExpr->op + " "  // recursivly calls generateExpression; handles cases like 'x + (y * 2)'
            + generateExpression(binaryExpr->right) + ")";
    }
    throw std::runtime_error("Unknown expression type");
}

std::string variableDeclaration(const std::string& varType, const std::string& identifier, const Expression* initializer) {
    std::string output = mapType(varType) + " " + identifier;
    if (initializer)
        output += " = " + generateExpression(initializer);
    return output + ";\n";
}