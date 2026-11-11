#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "../Lexer/Lexer.h" // Get Token Class
#include "../Parser/AST.h"  // Get AST class

//Honestly I have not idea what to put here, just ignore this for now I guess

class SemAnalysis {
    private:
        //put variables of AST tree and ways of looking at tree
        //create a variable table, for holding variables to then send to IR
        bool analysis;
        ASTNode node;
        std::string fMessage;
        std::vector<std::string> varScope;

    public:

        void isFalse() {
            analysis = false;
            fMessage = "Semantic Analysis Error!";
        }

        bool Analysis(){ return Analysis;}

        std::vector<std::string> scope(){ return varScope;}

        SemAnalysis(Program* node);
};