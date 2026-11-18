#include <iostream>
#include <vector>
#include <string>

#include "Driver.h"
#include <cstdlib>
#include <stdexcept>
#include <string>

int RunCompiler(const std::string& inputPath)
{
    try
    {
        // 1. Run Lexer
        std::vector<Token> tokens = RunLexerProgram(inputPath);

        std::cout << "[SUCCESS] Lexer completed.\n";

        // 2. Run Parser
        Parser parser(tokens);
        ASTNode* ast = parser.Parse();

        if (!ast) {
            throw std::runtime_error("Parser returned empty AST.");
        }
        std::cout << "[SUCCESS] Parser completed.\n";

        // 3. Run Code Generator
        Program* program = dynamic_cast<Program*>(ast);

        if (!program)
        {
            throw std::runtime_error("Failed to generate Program AST.");
        }

        std::string cppPath = GenerateCode(program);

        std::cout << "[SUCCESS] Code generation completed.\n";

        // 4. Final confirmation
        std::cout << "\nCompilation completed successfully!\n";
        std::cout << "C++ output file: " << cppPath << "\n";

        //5.  CLANG
        std::cout << "CLANG Compiling\n";

        int compileResult = std::system(
            ("clang++ -std=c++17 " + cppPath + " -o output.exe").c_str()
        );

        if (compileResult != 0) {
            std::cerr << "CLANG Failed\n";
            return 1;
        }

        std::cout << "CLANG Passed\n";

        std::cout << "Running...\n";

        int runResult = std::system("output.exe");

        return runResult;

    }
    catch (const std::exception& e)
    {
        std::cerr << "[ERROR] Compilation failed: " << e.what() << "\n";
        return 1;
    }
}
