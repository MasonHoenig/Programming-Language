// An example test suite file
#include "../Run_Tests.h"
#include "../../Source Code/Lexer/Lexer.cpp"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.
testReturn lexerTests(){
    std::string input1 = "variable number x = 1;";
    std::string input2 = "variable word w = \"hello\";";
    std::string input3 = "variable letter let1 = 'a';";
    std::string input4 = "variable bool b = true;";
    std::string input5 = "x = (x + 3.4) * 5;"; //assumes x is already defined
    std::string input6 = "if (x >= 0) { return true; }";

    //note: lexer may only have to handle unknown token type errors
    std::string input7 = "variable number x = 1"; //invalid input, missing ;
    std::string input8 = "brr number x = 5;"; //invalid input, brr is UNKNOWN
    std::string input9 = "variable number x = \"hello\";"; //invalid input, number cannot be assigned a string
    std::string input10 = "if (x >= 0 { return true; }"; //invalid input, missing )
    std::string input11 = "if (\"hello\" >= 0) { return true; }"; //invalid input, imcompatible types
    std::string input12 = "function number func() { word x = \"hello\"; return x; }"; //invalid input, function return type is number but returns a string
    std::string input13 = "variable decimal d = 3.14 / 0;"; //invalid input, division by zero
    //std::string input14 = "variable number x = arr[5];"; //invalid input, assumes arr has < 5 elements

    //comment tests
    std::string input15 = "variable number x = 1; // This is a comment"; //valid input
    std::string input16 = "variable number x = y /* alread defined */ + 1;"; //valid input
    std::string input17 = "variable number x = y /* alread defined + 1;"; //invalid input

    std::string correctOutput = "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (Integer,1), (Semicolon,;)]";
    std::string correctOutput2 = "[(Keyword,variable), (VarType,word), (VarName,w), (Assign,=), (Quote,\"), (Word,hello), (Quote,\"), (Semicolon,;)]";
    std::string correctOutput3 = "[(Keyword,variable), (VarType,letter), (VarName,let1), (Assign,=), (Quote,\'), (SingleChar,a), (Quote,\'), (Semicolon,;)]";
    std::string correctOutput4 = "[(Keyword,variable), (VarType,bool), (VarName,b), (Assign,=), (BoolValue,true), (Semicolon,;)]";
    std::string correctOutput5 = "[(VarName,x), (Assign,=), (Parentheses,(), (VarName,x), (Math,+), (Decimal,3.4), (Parentheses,)), (Math,*), (Integer,5), (Semicolon,;)]";
    std::string correctOutput6 = "[(Keyword,if), (Parentheses,(), (VarName,x), (Comparison,>=), (Integer,0), (Parentheses,)), (Parentheses,{), (Keyword,return), (BoolValue,true), (Semicolon,;), (Parentheses,})]";
    std::string correctOutput7 = "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (Integer,1), (Semicolon,;)]";
    std::string correctOutput8 = "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (VarName,y), (Math,+), (Integer,1), (Semicolon,;)]";
    
    //Collum number will be added when all tests pass
    //IDEA: No collum number, errors read: Error! <error type>: <print line>
    std::string incorrectOutput = "Error! Missing Semicolon: variable number x = 1"; //Col 21
    std::string incorrectOutput2 = "Error! Unknown token type: brr: brr number x = 5;"; //Col 1
    std::string incorrectOutput3 = "Error! Invalid assignment: variable number x = \"hello\";"; //Col 22, unsure if Col is right
    std::string incorrectOutput4 = "Error! Missing Parentheses: if (x >= 0 { return true; }"; //Col 27
    std::string incorrectOutput5 = "Error! Incompatible types: if (\"hello\" >= 0) { return true; }"; //Col is supposed to be "return"'s Col, not sure what it is
    std::string incorrectOutput6 = "Error! Function return type mismatch: function number func() { word x = \"hello\"; return x; }";
    std::string incorrectOutput7 = "Error! Division by zero: variable decimal d = 3.14 / 0;";
    //std::string incorrectOutput8 = "Error! Array index out of bounds";
    std::string incorrectOutput9 = "Error! Unclosed comment block: variable number x = y /* alread defined + 1;";

    //outputs of the inputs will be compared to the correct output. If they match, the test passes. If not, it fails.
    std::string output1 = RunLexerTest(input1);
    std::string output2 = RunLexerTest(input2);
    std::string output3 = RunLexerTest(input3);
    std::string output4 = RunLexerTest(input4);
    std::string output5 = RunLexerTest(input5);
    std::string output6 = RunLexerTest(input6);
    std::string output7 = RunLexerTest(input7);
    std::string output8 = RunLexerTest(input8);
    std::string output9 = RunLexerTest(input9);
    std::string output10 = RunLexerTest(input10);
    std::string output11 = RunLexerTest(input11);
    std::string output12 = RunLexerTest(input12);
    std::string output13 = RunLexerTest(input13);
    //std::string output14 = RunLexerTest(input14);
    std::string output15 = RunLexerTest(input15);
    std::string output16 = RunLexerTest(input16);
    std::string output17 = RunLexerTest(input17);

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

    if (output11 == incorrectOutput5) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 11 failed: Expected " + incorrectOutput5 + " but got " + output11 + "\n");
    }

    if (output12 == incorrectOutput6) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 12 failed: Expected " + incorrectOutput6 + " but got " + output12 + "\n");
    }

    if (output13 == incorrectOutput7) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 13 failed: Expected " + incorrectOutput7 + " but got " + output13 + "\n");
    }

    /*if (output14 == incorrectOutput8) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 14 failed: Expected " + incorrectOutput8 + " but got " + output14 + "\n");
    }*/

    if (output15 == correctOutput7) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 15 failed: Expected " + correctOutput7 + " but got " + output15 + "\n");
    }

    if (output16 == correctOutput8) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 16 failed: Expected " + correctOutput8 + " but got " + output16 + "\n");
    }

    if (output17 == incorrectOutput9) {
        passFail.passed++;
    } else {
        passFail.failed++;
        passFail.errorMessages.push_back("Test 17 failed: Expected " + incorrectOutput9 + " but got " + output17 + "\n");
    }

    passFail.errorMessages.push_back(""); //Add an empty string to the error vector.
    return passFail;
}