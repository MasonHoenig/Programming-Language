#include "TacToCpp.h"
#include "../Intermediate Representation/TAC.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

std::vector<std::string> emitCpp(const std::vector<std::vector<TAC>>& ir) {
    VariableDeclaration decl;
    std::vector<std::string> cppCode;

    for (const std::vector<TAC>& sourceLine : ir) {
        for (const TAC& instr : sourceLine) {
            cppCode.push_back(decl.variableDeclaration(instr));
        }
    }
    return cppCode;
}

int main() {
	std::string tempText = "Hello World";   // Just for testing; in practice, this will come from the lexer or AST string token.

    //vector of vector of TACs
    // First vector represents each line of code (size = num of lines of source code)
    // each TAC makes up that line of code  

    std::vector<std::vector<TAC>> testIR = {
        { { "=", "x", "5" } },                       // int
        { { "=", "y", "10.5" } },                    // double
        { { "=", "z", "true" } },                    // bool
        { { "=", "s", "\"" + tempText + "\"" } },    // string
        { { "=", "a", "x" } },                       // a copies x's type (int)
        { { "=", "x", "6" } },                       // reassign x
    };

    // use starting point and length to get string from source code.
    // or grab from Lexer or AST directly (if they store)

    for (const std::string& line : emitCpp(testIR)) {
        std::cout << line;
    }
}