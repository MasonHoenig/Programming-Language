// An example test suite file
#include "../Run_Tests.h"
#include "../../Source Code/Semantic Analysis/SemanticAnalysis.cpp"
#include "../../Source Code/Parser/AST.h"
#include "../../Source Code/Lexer/Lexer.cpp"
#include "../../Source Code/Parser/Parser.cpp"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.

ASTNode createASTNode(std::string)
{
    //run through Lexer

    //run through Parser to create ASTNode
    ASTNode node;
    return node;
}

testReturn semanticTests(){
    ASTNode i1 = createASTNode("Start {variable number x = 5;x = x + y;}");
    ASTNode i2 = createASTNode("Start {if(1 == 1) {variable number x = 5;}print(x);}");
    ASTNode i3 = createASTNode("Start {variable decimal x = 1.5;x = x + 5;}");
    ASTNode i4 = createASTNode("function number add(number n1, number n2) {return n1 + n2;}Start {add(6);}");
    ASTNode i5 = createASTNode("Start {Variable number x = 42;Variable word y = “word”;Variable array number NumberArray[4];number[0] = x;print(y);}");
    
    std::string o1 = runSemTest(i1);
    std::string o2 = runSemTest(i2);
    std::string o3 = runSemTest(i3);
    std::string o4 = runSemTest(i4);
    std::string o5 = runSemTest(i5);

    std::string co1 = "";
    std::string co2 = "";
    std::string co3 = "";
    std::string co4 = "";
    std::string co5 = "";

    testReturn passFail; //If you come up with a better name, feel free to change it.
    passFail.passed = 0;
    passFail.failed = 0;

    if(o1 == co1){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co1 + " but got " + o1 + "\n");
    }

    if(o2 == co2){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co2 + " but got " + o2 + "\n");
    }

    if(o3 == co3){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co3 + " but got " + o3 + "\n");
    }

    if(o4 == co4){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co4 + " but got " + o4 + "\n");
    }
    if(o5 == co5){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co4 + " but got " + o4 + "\n");
    }

    passFail.errorMessages.push_back(""); //Add an empty string to the error vector.
    return passFail;
}