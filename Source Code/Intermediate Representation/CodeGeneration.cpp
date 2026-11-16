#include "CodeGeneration.h"

#include <iostream>
#include <fstream>

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


void handleStatement(Statement* statement, std::ofstream* output){

    bool validPolyClass = false; //Set this to true at the beginning of all the statement handling

    
    if (const VariableDeclaration *varDec = dynamic_cast<const VariableDeclaration *>(statement))
    {
        validPolyClass = true;

        std::string strOutput = mapType(varDec->varType) + " " + varDec->identifier;
        if (varDec->initializer)
        {
            strOutput += " = " + generateExpression(varDec->initializer);
        }
        else
        {
            std::cerr << "Fatal Error: VariableDeclaration Statement contains no initializer";
            exit(EXIT_FAILURE);
        }

        *output << strOutput << ";\n";
    }
    
    if (const IfStatement *ifState = dynamic_cast<const IfStatement *>(statement))
    {
        validPolyClass = true;

        std::cerr << "Error: Function not yet implemented";
        exit(EXIT_FAILURE);
    }
    
    if (const WhileLoop *whiLoop = dynamic_cast<const WhileLoop *>(statement))
    {
        validPolyClass = true;

        std::cerr << "Error: Function not yet implemented";
        exit(EXIT_FAILURE);
    }
    
    if (const ArrayDeclaration *arrDec = dynamic_cast<const ArrayDeclaration *>(statement))
    {
        validPolyClass = true;

        std::cerr << "Error: Function not yet implemented";
        exit(EXIT_FAILURE);

    }
    
    if (const FunctionDeclaration *funDec = dynamic_cast<const FunctionDeclaration *>(statement))
    {
        validPolyClass = true;

        std::cerr << "Error: Function not yet implemented";
        exit(EXIT_FAILURE);

    }
    
    if (const ForLoop *forLp = dynamic_cast<const ForLoop *>(statement))
    {
        validPolyClass = true;

        std::cerr << "Error: Function not yet implemented";
        exit(EXIT_FAILURE);

    }
    if(!validPolyClass){
        std::cerr << "Error: Unrecognised Statement type";
        exit(EXIT_FAILURE);
    }
}

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