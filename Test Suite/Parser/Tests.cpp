// An example test suite file
#include "../Run_Tests.h"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.

int passed = 0;
int failed = 0;
std::vector<std::string> errors = {};

//-----Test 1----- 
// Source Code = x=1;
// Lexer Input: [(Keyword, variable), (VarType, number), (VarName, "x"), (Assign, "="), (Integer, "1"), (Semicolon, ";")]
// Lexer Output: AST Printer prints: 
//Program
//└── VariableDeclaration
//    ├── Type: number
//    ├── Identifier: x
//    └── Initializer: LiteralExpression
//        └── Value: 1
void test1(){
    // Call Parser script with above input and compare output with expected output above, update global vars
    std::string expectedOutput = "Program -- VariableDeclaration - Type: number - Identifier: x - Initializer: LiteralExpression -- Value: 1";

    std::string realOutput = "Test";
    std::string error = "Parser Test 1 output does not match";

    if (expectedOutput == realOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

testReturn parserTests(){ // This function is called and returns the struct. I will call each test as a function and use global vars to return

    test1();

    testReturn passFail; 
    passFail.passed = passed;
    passFail.failed = failed;
    passFail.errorMessages = errors;
    return passFail;
}