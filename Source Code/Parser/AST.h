#pragma once

#include <string>
#include <vector>
#include "../Lexer/Lexer.h" // Get Token Class

class ASTNode {
public:
    SourceLocation location; // Needed for Semantic Analysis errors
    virtual ~ASTNode() = default; // Virtual destructor cleanup
};

// Base class for statements
class Statement : public ASTNode {};

// Base class for expressions
class Expression : public ASTNode {};

// Base class for root node
class Program : public ASTNode {
public:
    std::vector<Statement*> declarations; 
};

// ---Expression Classes---

class LiteralExpression : public Expression {
public:
    std::string value; // Ex: "1", "true", "Hello"
    TokenType type; // Ex: Integer, Bool, Word
};

class IdentifierExpression : public Expression {
public:
    std::string name; // Ex: "x" as variable being referenced
};

class BinaryExpression : public Expression {
public:
    Expression* left; // Left side of operation
    TokenType op; // The operator Ex: +, -, =, <, ect
    Expression* right; // The right side of the operation
};

// ---Standard Statements---

class VariableDeclaration : public Statement {
public:
    std::string varType; // Ex: number, word
    std::string identifier; // Variable Name
    Expression* initializer; // Right side of equals sign
};

class IfStatement : public Statement {
public:
    Expression* condition; // What is evaluated to true/false
    std::vector<Statement*> thenBranch; // The block of code if true
    std::vector<Statement*> elseBranch; // Optional else block
};

class WhileLoop : public Statement {
public:
    Expression* condition; // What is evaluated to true or false
    std::vector<Statement*> body; // Block of code if true
};

// ---Swine Specific---

class GotoStatement : public Statement {
public:
    std::string destinationNode; // Name of the node to transition to
};

class OptionStatement : public Statement {
public:
    Expression* displayText; // Text to show the user
    GotoStatement* transition; // The goto associated with this option
};

class OptionSetStatement : public Statement {
public:
    std::vector<OptionStatement*> options; // Collection of choices for user
};

class NodeDeclaration : public Statement {
public:
    std::string nodeName; // Name of the node ex: "Castle"
    std::vector<Statement*> body; // The statements inside the node block
};