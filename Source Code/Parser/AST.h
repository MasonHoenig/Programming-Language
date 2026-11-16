#pragma once

#include <string>
#include <vector>
#include "../Lexer/Lexer.h" // Get Token Class

class ASTNode {
public:
    //SourceLocation location; // Needed for Semantic Analysis errors, comes from Lexer
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
    std::string op; // The operator Ex: +, -, =, <, ect
    Expression* right; // The right side of the operation
};

class UnaryExpression : public Expression {
public:
    std::string op; // The operator Ex: not, -
    Expression* right; // The expression being operated on
};

class FunctionCallExpression : public Expression {
public:
    std::string functionName; // Ex: "print"
    std::vector<Expression*> arguments; // The variables or literals passed in
};

class ArrayAccessExpression : public Expression {
public:
    std::string arrayName; // Ex: "NumberArray"
    Expression* index; // The index being accessed, Ex: 0
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

class ArrayDeclaration : public Statement {
public:
    std::string varType; // Ex: number
    std::string identifier; // Variable Name
    Expression* size; // The size inside the brackets
    std::vector<Expression*> elements; // The initialized elements, if any
};

class FunctionDeclaration : public Statement {
public:
    std::string returnType; // Ex: void, word
    std::string name; // Function name
    std::vector<std::pair<std::string, std::string>> parameters; // Pair of <Type, Name>
    std::vector<Statement*> body; // The code block inside the function
};

class ForLoop : public Statement {
public:
    Statement* initialization; // Ex: variable number y = 0
    Expression* condition; // Ex: y < 5
    Statement* update; // Ex: y = y + 1
    std::vector<Statement*> body; // The code block
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