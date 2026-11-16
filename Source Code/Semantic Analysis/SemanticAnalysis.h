#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include "../Lexer/Lexer.h" // Get Token Class
#include "../Parser/AST.h"  // Get AST class

class SemAnalysis {
    private:
        bool analysis;
        ASTNode node;
        std::string fMessage;
        std::stack<std::unordered_map<std::string, std::string>> Scope;//in map, std::string is variable name, second std::string is the variable type

    public:

        void isFalse() {
            analysis = false;
            fMessage = "Semantic Analysis Error!";
        }

        bool Analysis(){ return Analysis;}

        std::stack<std::unordered_map<std::string, std::string>> Sc() {
            return Scope;
        }

        SemAnalysis(Program* node);
};