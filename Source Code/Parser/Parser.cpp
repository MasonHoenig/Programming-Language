#include "Parser.h"
#include <stdexcept>
#include <sstream>

//Constructor and Traversal

Parser::Parser(const std::vector<Token>& inputTokens){
    tokens = inputTokens;
    currentIndex = 0;
}

bool Parser::isAtEnd(){
    return currentIndex >= tokens.size();
}

Token Parser::peek() {
    if (isAtEnd()){
        //Return EOF token 
        Token eofToken;
        eofToken.value = "EOF";
        return eofToken;
    }
    return tokens[currentIndex];
}

Token Parser::advance(){
    if (!isAtEnd()){
        currentIndex++;
    }
    return tokens[currentIndex - 1];
}

bool Parser::match(TokenType expectedType){
    if (isAtEnd() || peek().type != expectedType){
        //throw a standard error for now, later push to diagnostic vector 
        throw std::runtime_error("Syntax Error: Unexpected token '" + peek().value + "'");
    }
    advance();
    return true;
}

//Parsing logic for recursive descent

ASTNode* Parser::Parse(){
    return parseProgram();
}

Statement* Parser::parseStatement(){
    //look at current token to see kind of statement

    if(peek().type == TokenType::Keyword){
        return parseVariableDeclaration();
    }
    //If it does not match anything throw error
    throw std::runtime_error("Syntax Error: Unknown statement starting with '" + peek().value + "'");
}

VariableDeclaration* Parser::parseVariableDeclaration(){
    VariableDeclaration* decl = new VariableDeclaration();

    // 1. Consume 'variable' keyword
    match(TokenType::Keyword);

    // 2. Grab the type and consume 
    decl->varType = peek().value;
    match(TokenType::VarType);

    // 3. Grab identifier name and consume
    decl->identifier = peek().value;
    match(TokenType::VarName);

    // 4. Consume '=' sign
    match(TokenType::Assign);

    // 5. Parse right side of equals
    decl->initializer = parseExpression();

    // 6. Consume the simicolon
    match(TokenType::Semicolon);

    return decl;
}

Expression* Parser::parseExpression(){
    //For now just parse literal, later do parseComparison -> parseArithmatic -> parsePrimary
    return parsePrimary();
}

Expression* Parser::parsePrimary(){
    //Check if token is a literal 
    if (peek().type == TokenType::Integer){
        LiteralExpression* expr = new LiteralExpression();
        expr->value = peek().value;
        expr->type = peek().type;
        advance(); // consume number
        return expr;
    }
    //throw error if not found
    throw std::runtime_error("Syntax Error: Expected expression, found '" + peek().value + "'");
}

//AST Printer 

std::string Parser::PrintTree(ASTNode* node){
    if (!node) return "";

    std::ostringstream output;

    //Check if program root node
    if (Program* prog = dynamic_cast<Program*>(node)){
        output << "Program\n";
        for (Statement* stmt : prog->declarations){
            output << PrintTree(stmt); // recursive call all top level stmt
        }
    }

    //Check if node is var declaration
    else if (VariableDeclaration* varDecl = dynamic_cast<VariableDeclaration*>(node)){
        output << "└── VariableDeclaration\n";
        output << "    ├── Type: " << varDecl->varType << "\n";
        output << "    ├── Identifier: " << varDecl->identifier << "\n";
        output << "    └── Initializer: ";

        //print right side of assignment
        output << PrintTree(varDecl->initializer);
    }

    //Check if node is literal expression
    else if (LiteralExpression* litExpr = dynamic_cast<LiteralExpression*>(node)){
        output << "LiteralExpression\n";
        output << "        └── Value: " << litExpr->value;
    }
    return output.str();
}