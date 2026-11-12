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
    if (LiteralExpression* literal = dynamic_cast<const LiteralExpression*>(expr))
        return literal->value;

    if (IdentifierExpression* identifier = dynamic_cast<const IdentifierExpression*>(expr))
        return identifier->name;

    if (BinaryExpression* binaryExpr = dynamic_cast<const BinaryExpression*>(expr)) {
        return "(" + generateExpression(binaryExpr->left) + " " + binaryExpr->op + " "  // recursivly calls generateExpression; handles cases like 'x + (y * 2)'
            + generateExpression(binaryExpr->right) + ")";
    }

    // add expressions as we go (unary, functional, array, etc.)
    
    throw std::runtime_error("Unknown expression type");
}

std::string variableDeclaration(const std::string& varType, const std::string& identifier, const Expression* initializer) {
    std::string output = mapType(varType) + " " + identifier;
    if (initializer)
        output += " = " + generateExpression(initializer);
    return output + ";\n";
}