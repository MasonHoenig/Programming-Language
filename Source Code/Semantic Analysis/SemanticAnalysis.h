#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "../Lexer/Lexer.h" // Get Token Class
#include "../Parser/AST.h"  // Get AST class

//Honestly I have not idea what to put here, just ignore this for now I guess

// class SemAnalysis {
//     private:
//         //put variables of AST tree and ways of looking at tree
//         //create a variable table, for holding variables to then send to IR

//     public:
//         //putting tests here:
//         bool variableDec(VariableDeclaration node){
//             //don't have to worry if variable is a resticted word, as the lexer will catch it before
//             //main focus on if variable has already been declared, then putting it into the variable table
//             //Before that look to see if the value lines up with the type that is declared
            

            
//             return true;
//         }

//         SemAnalysis(ASTNode node);
// };