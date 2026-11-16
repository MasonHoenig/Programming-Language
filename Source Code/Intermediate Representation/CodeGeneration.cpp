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
        throw std::runtime_error("Unknown type: " + type);
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

    // add expressions as we go (unary, functional, array, etc.)
    
    throw std::runtime_error("Unknown expression type");
}

std::string variableDeclaration(const std::string& varType, const std::string& identifier, const Expression* initializer) {
    std::string output = mapType(varType) + " " + identifier;
    if (initializer)
        output += " = " + generateExpression(initializer);
    return output + ";\n";
}

std::string GenerateCode(const Program* program){

    std::ofstream outputFile("GeneratedCode.cpp");
    // outputFile << "Line to write goes here"; (Example for writing to a fstream operand.)
    if(!outputFile.is_open()){
        std::cerr << "Error: Unable to open/create file";
        exit(EXIT_FAILURE);
    }

    for(auto* statement : program->declarations){

        const VariableDeclaration *varDec = dynamic_cast<const VariableDeclaration *>(statement);
        if (varDec)
        { 
            outputFile << mapType(varDec->varType) + " " + varDec->identifier;
            if(varDec->initializer){ //Should always be true
                outputFile << " = ";
                outputFile << generateExpression(varDec->initializer);
                outputFile << ";" << std::endl;
            }else{
                std::cerr << "Fatal Error: VariableDeclaration Statement contains no initializer";
                exit(EXIT_FAILURE);
            }
            continue;
        }
        const IfStatement *ifState = dynamic_cast<const IfStatement *>(statement);
        if (ifState)
        {
            std::cerr << "Error: Function not yet implemented";
            exit(EXIT_FAILURE);

            //Uncomment the next line when finished writing this part of the function so the default case works properly.
            //continue;
        }
        const WhileLoop *whiLoop = dynamic_cast<const WhileLoop *>(statement);
        if (whiLoop)
        {
            std::cerr << "Error: Function not yet implemented";
            exit(EXIT_FAILURE);

            //Uncomment the next line when finished writing this part of the function so the default case works properly.
            //continue;
        }
        const ArrayDeclaration *arrDec = dynamic_cast<const ArrayDeclaration *>(statement);
        if (arrDec)
        {
            std::cerr << "Error: Function not yet implemented";
            exit(EXIT_FAILURE);

            //Uncomment the next line when finished writing this part of the function so the default case works properly.
            //continue;
        }
        const FunctionDeclaration *funDec = dynamic_cast<const FunctionDeclaration *>(statement);
        if (funDec)
        {  
            std::cerr << "Error: Function not yet implemented";
            exit(EXIT_FAILURE);

            //Uncomment the next line when finished writing this part of the function so the default case works properly.
            //continue;
        }
        const ForLoop *forLp = dynamic_cast<const ForLoop *>(statement);
        if (forLp)
        {
            std::cerr << "Error: Function not yet implemented";
            exit(EXIT_FAILURE);

            //Uncomment the next line when finished writing this part of the function so the default case works properly.
            //continue;
        }
        std::cerr << "Error: Unrecognised Statement type";
        exit(EXIT_FAILURE);
    }
}