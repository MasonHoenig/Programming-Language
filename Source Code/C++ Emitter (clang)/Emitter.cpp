#include "TacToCpp.h"
#include "../Intermediate Representation/TAC.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

std::vector<std::string> emitCpp(const std::vector<TAC>& ir) {
    VariableDeclaration decl;
    std::vector<std::string> cppCode;

    for (const TAC& instr : ir) {
        cppCode.push_back(decl.variableDeclaration(instr, "Hello World"));
    }
    return cppCode;
}

int main() {
	std::string tempText = "Hello World";   // Just for testing; in practice, this will come from the lexer or AST string token. 

    std::vector<TAC> testIR = {
        { "=", "x", "5" },      // int
		{ "=", "y", "10.5" },   // double
		{ "=", "z", "true" },   // bool
        { "=", "s", "\"" + tempText + "\"" },  // string        // see if we can call the operand like =str instead.
        { "=", "a", "x" },      // assign x to a
        { "=", "b", "y" },      // assign y to b
        { "=", "x", "y" },      // assign x to y (type mismatch)
    };

    for (const auto& line : emitCpp(testIR)) {
        std::cout << line;
    }
}