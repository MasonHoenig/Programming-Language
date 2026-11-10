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

    for (const std::vector<TAC>& line : ir) {   // foreach line in IR output
        for (const TAC& tac : line) {         // foreach TAC on each line
            cppCode.push_back(decl.variableDeclaration(tac));
        }
    }
    return cppCode;
}

int main() {
	std::string tempText = "Hello World";   // Just for testing; in practice, this will come from the lexer or AST string token. 

    std::vector<std::vector<TAC>> testIR = {
        { { "=", "x", "5" } },                       // int
        { { "=", "y", "10.5" } },                    // double
        { { "=", "z", "true" } },                    // bool
        { { "=", "s", "\"" + tempText + "\"" } },    // string
        { { "=", "a", "x" } },                       // a copies x's type (int)
        { { "=", "x", "6" } },                       // reassign x
    };

    for (const auto& line : emitCpp(testIR)) {  // IR output is inputted here
        std::cout << line;
    }
}