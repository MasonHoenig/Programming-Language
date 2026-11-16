#include <iostream>
#include <vector>
#include <string>

#include "Driver.h"

void RunCompiler(const std::string& inputPath)
{
    try
    {
        // 1. Run Lexer
        std::vector<Token> tokens = RunLexerProgram(inputPath);

        std::cout << "[SUCCESS] Lexer completed.\n";

        // 2. Run Parser
        Parser parser(tokens);
        ASTNode* ast = parser.Parse();

        std::cout << "[SUCCESS] Parser completed.\n";

        // 3. Run Code Generator
        Program* program = dynamic_cast<Program*>(ast);

        if (!program)
        {
            throw std::runtime_error("Failed to generate Program AST.");
        }

        GenerateCode(program);

        std::cout << "[SUCCESS] Code generation completed.\n";

        // 4. Final confirmation
        std::cout << "\nCompilation completed successfully!\n";
        std::cout << "C++ output file: " << outputPath << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "[ERROR] Compilation failed: " << e.what() << "\n";
    }
}