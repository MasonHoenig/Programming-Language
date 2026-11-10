#include "../Run_Tests.h"
#include "../../Source Code/C++ Emitter (clang)/TacToCpp.h"
#include "../../Source Code/Intermediate Representation/TAC.h"
#include "Tests.h"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

// ------ HELPERS ------

static void check (testReturn& result, bool condition, const std::string& testName, const std::string& details = "") {
    if (condition) {
        result.passed++;
    }
    else {
        result.failed++;
        result.errorMessages.push_back("[FAIL] " + testName + (details.empty() ? "" : ": " + details));
    }
}

// ------ TEST CASES ------

static bool testVariableDeclaration() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::vector<std::vector<TAC>> testIR = {
		{ "=", "x", "5" }
	};
	std::string expectedOutput =
		"	int x = 5;\n";

	if (VariableDeclaration::variableDeclaration(testIR) == expectedOutput)
		return true;
	return false;
}

// Currenlty commented out because they're not yet implemented

//static bool testArithmeticOperations() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (arithmeticOperations(input) == expectedOutput)
//		return true;
//	return false;
//}
//
//static bool testBooleanExpressions() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (booleanExpressions(input) == expectedOutput)
//		return true;
//	return false;
//}
//
//static bool testControlFlow() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (controlFlow(input) == expectedOutput)
//		return true;
//	return false;
//}
//
//static bool testLoops() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (loops(input) == expectedOutput)
//		return true;
//	return false;
//
//}
//
//static bool testDataStructures() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (dataStructures(input) == expectedOutput)
//		return true;
//	return false;
//}
//
//static bool testFunctions() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (functions(input) == expectedOutput)
//		return true;
//	return false;
//}	
//
//static bool testNodeFamily() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
//		"label Node_Start\n"
// 
//	std::string expectedOutput =
//
//	if (nodeFamily(input) == expectedOutput)
//		return true;
//	return false;
//}
//
//static bool testGotoStatement() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (gotoStatement(input) == expectedOutput)
//		return true;
//	return false;
//
//}
//
//static bool testUserInput() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (userInput(input) == expectedOutput)
//		return true;
//	return false;
//}
//
//static bool testConsoleOutput() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
// 
//	if (consoleOutput(input) == expectedOutput)
//		return true;
//	return false;
//}
//
//static bool testErrorHandling() {
//	testReturn result;
//	result.passed = 0;
//	result.failed = 0;
//
//	std::string input =
// 
//	std::string expectedOutput =
//
//	if (errorHandling(input) == expectedOutput)
//		return true;
//	return false;
//}

// ------ TEST SUITE ENTRY POINT ------

testReturn emitterTests() {
    testReturn result;
    result.passed = 0;
    result.failed = 0;

	check(result, testVariableDeclaration(), "Variable Declaration Tests");
	//check(result, testArithmeticOperations(), "Arithmetic Operations Tests");
	//check(result, testBooleanExpressions(), "Boolean Expressions Tests");
	//check(result, testControlFlow(), "Control Flow Tests");
	//check(result, testLoops(), "Loops Tests");
	//check(result, testDataStructures(), "Data Structures Tests");
	//check(result, testFunctions(), "Functions Tests");
	//check(result, testNodeFamily(), "Node Family Tests");
	//check(result, testGotoStatement(), "Goto Statement Tests");
	//check(result, testUserInput(), "User Input Tests");
	//check(result, testConsoleOutput(), "Console Output Tests");
	//check(result, testErrorHandling(), "Error Handling Tests");

    return result;
}
