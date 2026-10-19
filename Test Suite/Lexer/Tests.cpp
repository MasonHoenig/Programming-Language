// An example test suite file
#include "../Run_Tests.h"
#include "../Lexer/Lexer.cpp"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.
testReturn lexerTests(){
    std::string input1 = "variable number x = 1;"; //valid input
    std::string input2 = "variable word w = \"hello\";"; //hardcoded input
    std::string input3 = "variable letter let1 = 'a';"; //hardcoded input
    std::string input4 = "variable bool b = true;"; //hardcoded input
    std::string input5 = "x = (x + 3.4) * 5;"; //hardcoded input, assumes x is already defined
    std::string input6 = "if (x >= 0) { return true; }"; //hardcoded input
    std::string input7 = "variable number x = 1"; //invalid input, missing ;
    std::string input8 = "brr number x = 5;"; //hardcoded invalid input, brr is UNKNOWN
    std::string input9 = "variable number x = \"hello\";"; //hardcoded invalid input, number cannot be assigned a string
    std::string input10 = "if (x >= 0 { return true; }"; //hardcoded invalid input, missing )

    std::string correctOutput = "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (Integer,1), (Semicolon,;)]";
    //std::string inCorrectOutput = "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (Integer,1)]";
    std::string correctOutput2 = "[(Keyword,variable), (VarType,word), (VarName,w), (Assign,=), (Quote,\"), (Word,hello), (Quote,\"), (Semicolon,;)]";
    std::string correctOutput3 = "[(Keyword,variable), (VarType,letter), (VarName,let1), (Assign,=), (Quote,\'), (SingleChar,a), (Quote,\'), (Semicolon,;)]";
    std::string correctOutput4 = "[(Keyword,variable), (VarType,bool), (VarName,b), (Assign,=), (BoolValue,true), (Semicolon,;)]";
    std::string correctOutput5 = "[(VarName,x), (Assign,=), (Parentheses,(), (VarName,x), (Math,+), (Decimal,3.4), (Parentheses,)), (Math,*), (Integer,5), (Semicolon,;)]";
    std::string correctOutput6 = "[(Keyword,if), (Parentheses,(), (VarName,x), (Comparison,>=), (Integer,0), (Parentheses,)), (Parentheses,{), (Keyword,return), (BoolValue,true), (Semicolon,;), (Parentheses,})";
    std::string incorrectOutput = "Error! Missing Semicolon";
    std::string incorrectOutput2 = "Error! Unknown token type: brr";
    std::string incorrectOutput3 = "Error! Invalid assignment";
    std::string incorrectOutput4 = "Error! Missing Parentheses";

    //outputs of the inputs will be compared to the correct output. If they match, the test passes. If not, it fails.
    std::string output1 = RunLexerTest(input1);
    std::string output2 = RunLexerTestHardCoded(input2);
    std::string output3 = RunLexerTestHardCoded(input3);
    std::string output4 = RunLexerTestHardCoded(input4);
    std::string output5 = RunLexerTestHardCoded(input5);
    std::string output6 = RunLexerTestHardCoded(input6);
    std::string output7 = RunLexerTest(input7);
    std::string output8 = RunLexerTestHardCoded(input8);
    std::string output9 = RunLexerTestHardCoded(input9);
    std::string output10 = RunLexerTestHardCoded(input10);

    testReturn passFail; //If you come up with a better name, feel free to change it.
    passFail.passed = 0;
    passFail.failed = 0;

    if (output1 == correctOutput) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 1 failed: Expected " + correctOutput + " but got " + output1 + "\n");
    }

    if (output2 == correctOutput2) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 2 failed: Expected " + correctOutput2 + " but got " + output2 + "\n");
    }

    if (output3 == correctOutput3) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 3 failed: Expected " + correctOutput3 + " but got " + output3 + "\n");
    }

    if (output4 == correctOutput4) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 4 failed: Expected " + correctOutput4 + " but got " + output4 + "\n");
    }

    if (output5 == correctOutput5) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 5 failed: Expected " + correctOutput5 + " but got " + output5 + "\n");
    }

    if (output6 == correctOutput6) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 6 failed: Expected " + correctOutput6 + " but got " + output6 + "\n");
    }

    if (output7 == incorrectOutput) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 7 failed: Expected " + incorrectOutput + " but got " + output7 + "\n");
    }

    if (output8 == incorrectOutput2) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 8 failed: Expected " + incorrectOutput2 + " but got " + output8 + "\n");
    }

    if (output9 == incorrectOutput3) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 9 failed: Expected " + incorrectOutput3 + " but got " + output9 + "\n");
    }

    if (output10 == incorrectOutput4) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 10 failed: Expected " + incorrectOutput4 + " but got " + output10 + "\n");
    }

    passFail.errorMessages.push_back(""); //Add an empty string to the error vector.
    return passFail;
}