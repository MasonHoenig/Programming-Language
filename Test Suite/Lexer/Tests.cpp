// An example test suite file
#include "../Run_Tests.h"
#include "../Lexer/Lexer.cpp"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.
testReturn lexerTests(){
    std::string input1 = "variable number x = 1;"; //valid input
    std::string input2 = "variable nuber x = 1"; //invalid input
    
    std::string correctOutput = "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (Integer,1), (Semicolon,;)]";
    //outputs of the inputs will be compared to the correct output. If they match, the test passes. If not, it fails.
    std::string output1 = RunLexerTest(input1);
    std::string output2 = RunLexerTest(input2);

    //how does this work?
    testReturn passFail; //If you come up with a better name, feel free to change it.
    passFail.passed = 0;
    passFail.failed = 0;

    if (output1 == correctOutput) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + correctOutput + " but got " + output1 + "\n");
    }

    if (output2 == correctOutput) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 2 failed: Expected " + correctOutput + " but got " + output2);
    }

    passFail.errorMessages.push_back(""); //Add an empty string to the error vector.
    return passFail;
}