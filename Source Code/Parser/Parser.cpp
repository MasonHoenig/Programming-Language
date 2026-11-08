#include "AST.h"
#include "Parser.h"

void HardcodeASTExample() {

    // ex: variable number x=1;

    Program* root = new Program();

    VariableDeclaration* varDecl = new VariableDeclaration();
    varDecl->varType = "number";
    varDecl->identifier = "x";

    LiteralExpression* literal1 = new LiteralExpression();
    literal1->value = "1";
    literal1->type = TokenType::Integer; // Assuming this exists in your Lexer

    varDecl->initializer = literal1;

    root->declarations.push_back(varDecl);
}

// R"(Program
// └── VariableDeclaration
//     ├── Type: number
//     ├── Identifier: x
//     └── Initializer: LiteralExpression
//         └── Value: 1)";

