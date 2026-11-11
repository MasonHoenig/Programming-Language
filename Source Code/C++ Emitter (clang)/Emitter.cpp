#include "TacToCpp.h"
#include "../Intermediate Representation/TAC.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

int nextId = 0;
std::unordered_map<std::string, std::string> names;
std::unordered_map<std::string, std::string> types;

// Emitter function call in Driver (inputs IR output)
std::vector<std::string> emitCpp(const std::vector<std::vector<TAC>>& ir) {
    std::vector<std::string> cppCode;

    nextId = 0;
    names.clear();
    types.clear();

    for (const std::vector<TAC>& line : ir) {
        clearResultKeys();

        for (size_t i = 0; i < line.size(); ++i) {
            const TAC& tac = line[i];

            if (isArithmetic(tac.operand))
                cppCode.push_back(arithmeticOperations(tac, i));
            else if (isBooleanEx(tac.operand))
                cppCode.push_back(booleanExpressions(tac, i));
            else if (isVariableDecl(tac.operand))
                cppCode.push_back(variableDeclaration(tac));
        }
    }
    return cppCode;
}

int main() {
    std::vector<std::vector<TAC>> testIR = {
        { { "=", "x", "4" } },
        { { "=", "y", "5"} },
        { { "=", "x", "5" } },
        { { "+", "6", "5" } },
        { { ">", "x", "y"} },
        { { "=", "a", "17" } },
    };

    for (const auto& line : emitCpp(testIR)) {  // IR output is inputted here
        std::cout << line;
    }
}