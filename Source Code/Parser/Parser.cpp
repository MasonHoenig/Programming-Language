#include "Parser.h"
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

//Constructor and Traversal

Parser::Parser(const std::vector<Token>& inputTokens){
    tokens = inputTokens;
    currentIndex = 0;
}

bool Parser::isAtEnd(){
    //We are at end if out of bounds, OR if current token is EOF
    return currentIndex >= tokens.size() || tokens[currentIndex].type == TokenType::EndFileMarker;
}

Token Parser::peek() {
    if (currentIndex >= tokens.size()){
        // if we go out of bounds, return dummy EOF
        SourceLocation dummyLoc = {0,0,0};
        return Token(TokenType::EndFileMarker, "EOF", dummyLoc); // construct dumy EOF
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
        if (peek().value == "while"){
            return parseWhileLoop();
        } else if (peek().value == "variable" || peek().value == "constant") {
            return parseVariableDeclaration();
        }
    }

    if(peek().type == TokenType::VarName){
        return parseAssignment();
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

WhileLoop* Parser::parseWhileLoop(){
    WhileLoop* whil = new WhileLoop();

    // 1. Consume 'while' keyword
    match(TokenType::Keyword);

    // 2. Consume first parenthasis  "("
    match(TokenType::Parentheses);

    // 3. Get and Consume Condition
    whil->condition = parseExpression();
    // 4. Consume second parenthasis ")"
    match(TokenType::Parentheses);

    // 5. Consume first curly "{"
    match(TokenType::Parentheses);

    // 6. Loop over the body to get and consume body
    while (!isAtEnd() && peek().value != "}") {
        whil->body.push_back(parseStatement());
    }

    // 7. Consume last curly "}"
    match(TokenType::Parentheses);

    return whil;
}

AssignmentStatement* Parser::parseAssignment(){
    AssignmentStatement* asign = new AssignmentStatement();

    // 1. Grab and consume var name
    asign->identifier = peek().value;
    match(TokenType::VarName);

    // 2. Consume the "="
    match(TokenType::Assign);

    // 3. Parse right side
    asign->value = parseExpression();

    // 4. Consume the semicolon ";"
    match(TokenType::Semicolon);

    return asign;
}

Program* Parser::parseProgram() {
    Program* program = new Program();
    
    // Keep parsing until run out of tokens or hit the EOF
    while (!isAtEnd()) {
        program->declarations.push_back(parseStatement());
    }
    
    return program;
}

Expression* Parser::parseExpression() {
    // comparisons is top of ladder for now
    return parseComparison();
}

Expression* Parser::parseComparison() {
    // 1. Go down one level for left side
    Expression* leftNode = parseArithmetic();

    // 2. Check if the current token is a comparison operator (<, >, ==, <=, >=, !=)
    if (!isAtEnd() && peek().type == TokenType::Comparison) {
        std::string operatorString = peek().value;
        advance(); // Consume 

        // 3. Go down one level again for the right side
        Expression* rightNode = parseArithmetic();

        // 4. Build the node
        BinaryExpression* binExpr = new BinaryExpression();
        binExpr->left = leftNode;
        binExpr->op = operatorString;
        binExpr->right = rightNode;

        return binExpr; // Return the node
    }

    // If there was no comparison operator, just return the left side
    return leftNode;
}

Expression* Parser::parseArithmetic() {
    // 1. Go down to the bottom level to get left side
    Expression* leftNode = parsePrimary();

    // 2. While loop for chain math like 1 + 2 * 3
    while (!isAtEnd() && peek().type == TokenType::Math) {
        std::string operatorString = peek().value;
        advance(); // Consume the math operator (+, -, *, /, %)

        // 3. Grab the right side
        Expression* rightNode = parsePrimary();

        // 4. Build the node
        BinaryExpression* binExpr = new BinaryExpression();
        binExpr->left = leftNode;
        binExpr->op = operatorString;
        binExpr->right = rightNode;

        // 5. New binary expression becomes left side
        leftNode = binExpr; 
    }

    return leftNode;
}

Expression* Parser::parsePrimary() {
    Token current = peek();

    // Literals
    if (current.type == TokenType::Integer || current.type == TokenType::Decimal || 
        current.type == TokenType::Word || current.type == TokenType::BoolValue) {
        
        LiteralExpression* expr = new LiteralExpression();
        expr->value = current.value;
        expr->type = current.type; // Set type and value
        
        advance(); // Consume the literal
        return expr;
    }
    
    // Handle variable names (Identifiers) "x"
    if (current.type == TokenType::VarName) {
        IdentifierExpression* expr = new IdentifierExpression();
        expr->name = current.value; // Ex: "x"
        
        advance(); // Consume the variable name
        return expr;
    }

    // If we reach here, the token is not a valid expression
    throw std::runtime_error("Syntax Error: Expected expression, found '" + current.value + "'");
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
    // check if node is assignment
    else if (AssignmentStatement* assignStmt = dynamic_cast<AssignmentStatement*>(node)) {
        output << "└── AssignmentStatement\n";
        output << "    ├── Identifier: " << assignStmt->identifier << "\n";
        output << "    └── Value: \n";
        
        // Recursively print the right side of the equals sign
        output << "        " << PrintTree(assignStmt->value);
    }
    //Check if node is literal expression
    else if (LiteralExpression* litExpr = dynamic_cast<LiteralExpression*>(node)){
        output << "LiteralExpression\n";
        output << "        └── Value: " << litExpr->value;
    }
    //Check if node is while loop
    else if (WhileLoop* whileStmt = dynamic_cast<WhileLoop*>(node)) {
        output << "└── WhileLoop\n";
        output << "    ├── Condition: \n";
        output << "    │   " << PrintTree(whileStmt->condition);
        output << "    └── Body: \n";
        
        for (Statement* stmt : whileStmt->body) {
            output << "        " << PrintTree(stmt);
        }
    }
    // Check if node is a BinaryExpression
    else if (BinaryExpression* binExpr = dynamic_cast<BinaryExpression*>(node)) {
        output << "BinaryExpression\n";
        output << "        ├── Left: " << PrintTree(binExpr->left);
        output << "        ├── Operator: " << binExpr->op << "\n";
        output << "        └── Right: " << PrintTree(binExpr->right);
    }
    // Check if node is an IdentifierExpression
    else if (IdentifierExpression* idExpr = dynamic_cast<IdentifierExpression*>(node)) {
        output << "IdentifierExpression (" << idExpr->name << ")\n";
    }
    return output.str();
}