#pragma once
#include "../Intermediate Representation/TAC.h"

#include <optional>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <unordered_set>

enum class Type { Int, Double, Bool, String };

struct Symbol
{
    std::string cppName;
    Type type;
};

// ------ Helper Functions ------

std::unordered_set<std::string>& declaredNames();
void resetDeclared();
std::string declOrAssign(const std::string& type, const std::string& name);

bool isInteger(const std::string& str);
bool isDouble(const std::string& str);
bool isBoolean(const std::string& str);

std::string typeOf(const std::string& s);
std::string textOf(const std::string& s);

std::string escapeForCpp(const std::string& str);

bool isVariableDecl(const std::string& op);
bool isArithmetic(const std::string& op);
bool isBooleanEx(const std::string& op);

void clearResultKeys();

// ------------------------------

extern int nextId;
extern std::unordered_map<std::string, std::string> names;
extern std::unordered_map<std::string, std::string> types;

enum operations {
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo,
};

enum booleanEx {
    GreaterThan,
    LessThan,
    EqualTo,
    GreaterThanOrEqualTo,
    LessThanOrEqualTo,
    NotEqualTo,
    Or,
    And,
    Xor,
};

std::string variableDeclaration(const TAC& tac);

std::string arithmeticOperations(const TAC& tac, size_t index);

std::string booleanExpressions(const TAC& tac, size_t index);

std::ofstream emitCpp(const std::vector<std::vector<TAC>>& ir);