#include Driver.h

#include Lexer.h // Lexer
#include Parser.h // Parser
#include AST.h // Parser
////#include SematicAnalysis.h // Scematic Analysis
//#include IR.h // Intermediate Representation
//#include Emitter.h
//#include TacToCpp.h


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>



Driver::Driver(){}

    // pull source and into string
    std:string Driver::readFile(const std::string& filename) {
        std:ifstream file(filename);

        if(!file.is_open()){
            throw std::runtime_error("Could not open source file + filename");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }

int Driver::run(const std:string& sourceFile) {
    try {
        //read source

        std::cout << "Reading source\n";
        std::string source = readFile(sourceFile);

        // lexer

        std::cout << "Lexer running\n";
        std::vector<Token> tokens = RunLexerProgram(sourceFile);

        //parser

        std::cout << "Parser running\n";
        Parser parser(tokens);
        if (ast == nullptr) {
            std::cerr << "Parser failed to make AST\n";
            return 1;
        }

        // sematic analysis

            // sematic code tbd

        // IR

            // ir code tbd

        //emitter

            // emitter code waiting on IR

        // clang
        // tbd, needs more research
    }
}

