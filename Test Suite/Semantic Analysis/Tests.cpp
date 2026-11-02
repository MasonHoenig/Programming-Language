// An example test suite file
#include "../Run_Tests.h"
#include "../Semantic Analysis/SemanticAnalysis.cpp"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.

class ASTNode{}
class printNode : public ASTNode{}
class identiyNode : public ASTNode{}



testReturn semanticTests(){
    std::ASTNode i1;
    std::ASTNode i2;
    std::ASTNode i3;
    std::ASTNode i4;
    
    std::string o1 = runSemTest(i1);
    std::string o2 = runSemTest(i1);
    std::string o3 = runSemTest(i1);
    std::string o4 = runSemTest(i1);

    std::string co1 = "";
    std::string co2 = "";
    std::string co3 = "";
    std::string co4 = "";

    testReturn passFail; //If you come up with a better name, feel free to change it.
    passFail.passed = 0;
    passFail.failed = 0;

    if(o1 == 01){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co1 + " but got " + o1 + "\n");
    }

    if(o2 == 02){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co2 + " but got " + o2 + "\n");
    }

    if(o3 == 03){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co3 + " but got " + o3 + "\n");
    }

    if(o4 == 04){   
        passFail.passed++;
    }
    else{
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + co4 + " but got " + o4 + "\n");
    }

    passFail.errorMessages.push_back(""); //Add an empty string to the error vector.
    return passFail;
}