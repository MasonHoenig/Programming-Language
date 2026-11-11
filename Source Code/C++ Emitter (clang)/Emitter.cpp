#include "TacToCpp.h"
#include "../Intermediate Representation/TAC.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>

int nextId = 0;
std::unordered_map<std::string, std::string> names;
std::unordered_map<std::string, std::string> types;

// Emitter function call in Driver (inputs IR output)
std::ofstream emitCpp(const std::vector<std::vector<TAC>>& ir) {
    std::ofstream outputFile("output.cpp");

    if (!outputFile.is_open()) {
        throw std::runtime_error("Error: Could not open the file for writing.");
    }

    nextId = 0;
    names.clear();
    types.clear();

    for (const std::vector<TAC>& line : ir) {
        clearResultKeys();

        for (size_t i = 0; i < line.size(); ++i) {
            const TAC& tac = line[i];

            if (isArithmetic(tac.operand))
                outputFile << arithmeticOperations(tac, i) << std::endl;
            else if (isBooleanEx(tac.operand))
                outputFile << (booleanExpressions(tac, i)) << std::endl;
            else if (isVariableDecl(tac.operand))
                outputFile << (variableDeclaration(tac)) << std::endl;
        }
    }
    return outputFile;
}

//int main() {
//    std::vector<std::vector<TAC>> testIR = {
//        { { "=", "x", "4" } },
//        { { "=", "y", "5"} },
//        { { "=", "x", "5" } },
//        { { "+", "6", "5" } },
//        { { ">", "x", "y"} },
//        { { "=", "a", "17" } },
//    };
//
//    try {
//        std::ofstream generatedFile = emitCpp(testIR);      // writes it to ../Source Code/out/build/x64-debug/output.cpp
//        std::cout << "Code generation completed successfully!" << std::endl;
//    }
//    catch (const std::exception& e) {
//        std::cerr << e.what() << std::endl;
//        return 1;
//    }
//
//    return 0;
//}