#include "CodeGeneration.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <typeinfo>

// Recursively iterate through AST (A lot of this can probably be taken from the current IR logic)
//
// On each iteration:
//	Check the type (isVariableDecl, isArithmetic, isBooleanExpr, etc.)
//	Execute code generation
//	Write output to output.cpp line by line

std::string mapType(const std::string& type) {
    auto it = typeMap.find(type);
    if (it == typeMap.end()) //Something is up with this logic, should probably be looked at.
        exit(EXIT_FAILURE);
    return it->second;
}

// Takes Expression*, figures out what concrete type it is, and returns a string representing the complete expression.
// ---Expression Generation---
std::string generateExpression(const Expression* expr) {

    if (const LiteralExpression *literal = dynamic_cast<const LiteralExpression *>(expr))
        return literal->value;

    if (const IdentifierExpression* identifier = dynamic_cast<const IdentifierExpression*>(expr))
        return identifier->name;

    if (const BinaryExpression* binaryExpr = dynamic_cast<const BinaryExpression*>(expr)) {
        return "(" + generateExpression(binaryExpr->left) + " " + binaryExpr->op + " "  // recursively calls generateExpression; handles cases like 'x + (y * 2)'
            + generateExpression(binaryExpr->right) + ")";
    }
    if (const UnaryExpression* unaryExpr = dynamic_cast<const UnaryExpression*>(expr)) {
        return unaryExpr->op + "(" + generateExpression(unaryExpr->right) + ")";
    }
    if (const FunctionCallExpression *funcExpr = dynamic_cast<const FunctionCallExpression *>(expr)){
        //Placeholder
    }
    if (const ArrayAccessExpression *arrExpr = dynamic_cast<const ArrayAccessExpression *>(expr))
    {
        //Placeholder
    }

    std::cerr << "Error: Unimplemented Expression type called";
    exit(EXIT_FAILURE);
}

// ---Statement Generation---

std::string generateStatement(const Statement* statement, int indent) {
    if (const VariableDeclaration* decl = dynamic_cast<const VariableDeclaration*>(statement)) {
        std::string out = std::string(indent * 4, ' ') + mapType(decl->varType) + " " + decl->identifier;
        if (decl->initializer)
            out += " = " + generateExpression(decl->initializer);
        return out + ";\n";
    }
    if (const IfStatement* ifState = dynamic_cast<const IfStatement*>(statement)) {
        return generateIf(ifState, indent);
    }
    if (const WhileLoop* whileState = dynamic_cast<const WhileLoop*>(statement)) {
        // placeholder
    }
    if (const ForLoop* forState = dynamic_cast<const ForLoop*>(statement))
    {
        //Placeholder
    }
    if (const FunctionDeclaration* funcState = dynamic_cast<const FunctionDeclaration*>(statement)) {
        //Placeholder
    }
    if (const ArrayDeclaration* arrState = dynamic_cast<const ArrayDeclaration*>(statement))
    {
        //Placeholder
    }
    // unknown node: report it instead of silently dropping it. Runtime Error to make it visable in the console
    throw std::runtime_error(std::string("generateStatement: unhandled node ") + typeid(*statement).name());
}

// std::string swineSpecific () { }     -- implement similar to generate statements above

// helper for ifs, loops, etc.
std::string generateBlock(const std::vector<Statement*>& block, int indent) {
    std::string out;
    for (const Statement* s : block)
        out += generateStatement(s, indent);   // your existing dispatcher
    return out;
}

std::string generateIf(const IfStatement* node, int indent, bool isElseIf) {
    std::string pad(indent * 4, ' ');
    std::string output = isElseIf ? " else " : pad;
    output += "if (" + generateExpression(node->condition) + ") {\n";

    for (const Statement* statement : node->thenBranch)     // then branch handles boolean operations, no need for explicate calls here
        output += generateStatement(statement, indent + 1);
    output += pad + "}";
    
    if (node->elseBranch.empty())
        return output + "\n";

    if (node->elseBranch.size() == 1)
        if (IfStatement* nested = dynamic_cast<IfStatement*>(node->elseBranch[0]))
            return output + generateIf(nested, indent, true);   // recursion for else-if

    output += " else {\n";
    for (const Statement* statement : node->elseBranch)
        output += generateStatement(statement, indent + 1);
    return output + pad + "}\n";
}

// one liner here removes double check. Works well with recursive if-else, whiles, for, etc.
void handleStatement(Statement* statement, std::ofstream* output) {
    *output << generateStatement(statement, 0);
}

//void handleStatement(Statement* statement, std::ofstream* output){
//
//    bool validPolyClass = false; //Set this to true at the beginning of all the statement handling
//
//    if (const VariableDeclaration* decl = dynamic_cast<const VariableDeclaration*>(statement)) {
//        *output << generateStatement(statement, 0);
//    }
//    
//    if (const IfStatement *ifState = dynamic_cast<IfStatement *>(statement))
//    {
//        validPolyClass = true;
//        // this could be written inline, but its a longer function so I left it out for now.
//        *output << generateIf(ifState, 0);
//    }
//    
//    if (const WhileLoop *whiLoop = dynamic_cast<WhileLoop *>(statement))
//    {
//        validPolyClass = true;
//
//        std::cerr << "Error: Function not yet implemented";
//        exit(EXIT_FAILURE);
//    }
//    
//    if (const ArrayDeclaration *arrDec = dynamic_cast<const ArrayDeclaration *>(statement))
//    {
//        validPolyClass = true;
//
//        std::cerr << "Error: Function not yet implemented";
//        exit(EXIT_FAILURE);
//
//    }
//    
//    if (const FunctionDeclaration *funDec = dynamic_cast<const FunctionDeclaration *>(statement))
//    {
//        validPolyClass = true;
//
//        std::cerr << "Error: Function not yet implemented";
//        exit(EXIT_FAILURE);
//
//    }
//    
//    if (const ForLoop *forLp = dynamic_cast<const ForLoop *>(statement))
//    {
//        validPolyClass = true;
//
//        std::cerr << "Error: Function not yet implemented";
//        exit(EXIT_FAILURE);
//
//    }
//    if(!validPolyClass){
//        std::cerr << "Error: Unrecognised Statement type";
//        exit(EXIT_FAILURE);
//    }
//}

std::string GenerateCode(const Program* program) {

    std::string outputPath = "./GeneratedCode.cpp";
    std::ofstream outputFile(outputPath);

    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file : " + outputPath;
        exit(EXIT_FAILURE);
    }

    for(auto* statement : program->declarations){
        handleStatement(statement,&outputFile);
    }

    return outputPath;
}