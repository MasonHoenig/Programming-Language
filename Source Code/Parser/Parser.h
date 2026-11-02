#pragma once
#include <vector>
#include <string>
#include "../Lexer/Lexer.h" // Get Token Class
#include "AST.h"

class Parser{

private:
    std::vector<Token> tokens;
    size_t currentIndex; // Store exact position

    Token peek(); // Return the token we are looking at, does not consume
    Token peekNext(); // Returns the NEXT token
    Token advance(); // Consume the current token and move index forward

    bool isAtEnd(); // Check if we are out of tokens

    bool match(TokenType expectedType); // Check if current token matches expected type, consumes, if not throws error

    Program* parseProgram(); 

    //Statements Parsing
    Statement* parseStatement();
    VariableDeclaration* parseVariableDeclaration();
    IfStatement* parseIfStatement();
    WhileLoop* parseWhileLoop();

    //Swine Specific Parsing
    NodeDeclaration* parseNodeDeclaration(); // Ex: Node Castle { ... }
    OptionSetStatement* parseOptionSet(); // Ex: OptionSet { Option(...) -> Goto ...}

    //Expressions Parsing
    Expression* parseExpression();
    Expression* parseComparison();
    Expression* parseArithmetic();
    Expression* parsePrimary(); // For Literals

public:

    // Constructor takes token stream from the Lexer
    Parser(const std::vector<Token>& inputTokens);

    // The main entry point that starts the recursive descent 
    ASTNode* Parse();

    // Dumps AST into string for tests 
    std::string PrintTree(ASTNode* root);

};