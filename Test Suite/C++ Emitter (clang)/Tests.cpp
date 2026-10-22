#include "../Run_Tests.h"
#include "../../Source Code/C++ Emitter (clang)/Emitter.h"
#include "Tests.h"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

// ------ HELPERS ------

static std::string normalize(const std::string& s) {
    std::string out;
    bool pendingSpace = false;
    for (char c : s) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            pendingSpace = true;
            continue;
        }
        if(pendingSpace && !out.empty()) out += ' ';
        pendingSpace = false;
        out += c;
    }
    return out;
}

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

	std::string input =
		"decl i : number\n"
		"i = 1\n"
		"decl name : text\n"
		"name = \"hello\"\n"
		"decl done : boolean\n"
		"done = true\n";
	std::string expectedOutput =
		"int i;\n"
		"i = 1;\n"
		"std::string name;\n"
		"name = \"hello\";\n"
		"bool done;\n"
		"done = true;\n";

	if (variableDeclaration(input) == expectedOutput)
		return true;
	return false;
}

static bool testArithmeticOperations() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"decl a : number\n"
		"decl b : number\n"
		"a = 5\n"
		"b = 3\n"
		"t1 = b * 2\n"
		"t2 = a + t1\n"
		"t3 = t2 - 1\n"
		"t4 = t3 / 2\n"
		"t5 = t4 % 3\n";
	std::string expectedOutput =
		"int a;\n"
		"int b;\n"
		"a = 5;\n"
		"b = 3;\n"
		"auto t1 = b * 2;\n"
		"auto t2 = a + t1;\n"
		"auto t3 = t2 - 1;\n"
		"auto t4 = t3 / 2;\n"
		"auto t5 = t4 % 3;\n";

	if (arithmeticOperations(input) == expectedOutput)
		return true;
	return false;
}

static bool testBooleanExpressions() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"decl p : boolean\n"
		"decl q : boolean\n"
		"t1 = p and q\n"
		"t2 = p or q\n"
		"t3 = not p\n"
		"t4 = p xor q\n";
	std::string expectedOutput =
		"bool p;\n"
		"bool q;\n"
		"auto t1 = p && q;\n"
		"auto t2 = p || q;\n"
		"auto t3 = !p;\n"
		"auto t4 = (p != q);\n";   // C++ has no logical xor

	if (booleanExpressions(input) == expectedOutput)
		return true;
	return false;
}

static bool testControlFlow() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"decl x : boolean\n"
		"decl y : number\n"
		"x = true\n"
		"ifFalse x goto L1\n"
		"y = 1\n"
		"goto L2\n"
		"label L1\n"
		"y = 2\n"
		"label L2\n";
	std::string expectedOutput =
		"bool x;\n"
		"int y;\n"
		"x = true;\n"
		"if (!x) goto L1;\n"
		"y = 1;\n"
		"goto L2;\n"
		"L1:;\n"
		"y = 2;\n"
		"L2:;\n";

	if (controlFlow(input) == expectedOutput)
		return true;
	return false;
}

static bool testLoops() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"decl i : number\n"
		"i = 0\n"
		"label L1\n"
		"t1 = i < 10\n"
		"ifFalse t1 goto L2\n"
		"i = i + 1\n"
		"goto L1\n"
		"label L2\n";
	std::string expectedOutput =
		"int i;\n"
		"i = 0;\n"
		"L1:;\n"
		"auto t1 = i < 10;\n"
		"if (!t1) goto L2;\n"
		"i = i + 1;\n"
		"goto L1;\n"
		"L2:;\n";

	if (loops(input) == expectedOutput)
		return true;
	return false;

}

static bool testDataStructures() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"newarray nums : number, 3\n"
		"nums[0] = 10\n"
		"nums[1] = 20\n"
		"t1 = nums[1]\n";
	std::string expectedOutput =
		"std::vector<int> nums(3);\n"
		"nums[0] = 10;\n"
		"nums[1] = 20;\n"
		"auto t1 = nums[1];\n";

	if (dataStructures(input) == expectedOutput)
		return true;
	return false;
}

static bool testFunctions() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"func add(a : number, b : number) : number\n"
		"t1 = a + b\n"
		"return t1\n"
		"endfunc\n";
	std::string expectedOutput =
		"int add(int a, int b) {\n"
		"    auto t1 = a + b;\n"
		"    return t1;\n"
		"}\n";

	if (functions(input) == expectedOutput)
		return true;
	return false;
}	

static bool testNodeFamily() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"label Node_Start\n"
		"print \"You are in a dark room.\"\n"
		"option 1 \"Open the door\" Node_Door\n"
		"option 2 \"Stay put\" Node_Stay\n"
		"prompt\n"
		"label Node_Door\n"
		"print \"The door creaks open.\"\n"
		"label Node_Stay\n"
		"print \"Nothing happens.\"\n";
	std::string expectedOutput =
		"Node_Start:;\n"
		"std::cout << \"You are in a dark room.\" << '\\n';\n"
		"std::cout << \"1. Open the door\" << '\\n';\n"
		"std::cout << \"2. Stay put\" << '\\n';\n"
		"{\n"
		"    int choice = 0;\n"
		"    std::cin >> choice;\n"
		"    if (choice == 1) goto Node_Door;\n"
		"    if (choice == 2) goto Node_Stay;\n"
		"}\n"
		"Node_Door:;\n"
		"std::cout << \"The door creaks open.\" << '\\n';\n"
		"Node_Stay:;\n"
		"std::cout << \"Nothing happens.\" << '\\n';\n";

	if (nodeFamily(input) == expectedOutput)
		return true;
	return false;
}

static bool testGotoStatement() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;
	std::string input =
		"goto Node_End\n"
		"print \"skipped\"\n"
		"label Node_End\n";
	std::string expectedOutput =
		"goto Node_End;\n"
		"std::cout << \"skipped\" << '\\n';\n"
		"Node_End:;\n";

	if (gotoStatement(input) == expectedOutput)
		return true;
	return false;

}

static bool testUserInput() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"decl age : number\n"
		"decl name : text\n"
		"read_number age\n"
		"read_text name\n";
	std::string expectedOutput =
		"int age;\n"
		"std::string name;\n"
		"std::cin >> age;\n"
		"std::getline(std::cin, name);\n";

	if (userInput(input) == expectedOutput)
		return true;
	return false;
}

static bool testConsoleOutput() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"decl score : number\n"
		"score = 42\n"
		"print \"Hello, world!\"\n"
		"print score\n";
	std::string expectedOutput =
		"int score;\n"
		"score = 42;\n"
		"std::cout << \"Hello, world!\" << '\\n';\n"
		"std::cout << score << '\\n';\n";

	if (consoleOutput(input) == expectedOutput)
		return true;
	return false;
}

static bool testErrorHandling() {
	testReturn result;
	result.passed = 0;
	result.failed = 0;

	std::string input =
		"decl x : number\n"
		"frobnicate x\n";
	std::string expectedOutput =
		"ERROR: unknown instruction 'frobnicate' at line 2\n";

	if (errorHandling(input) == expectedOutput)
		return true;
	return false;
}

// ------ TEST SUITE ENTRY POINT ------

testReturn emitterTests() {
    testReturn result;
    result.passed = 0;
    result.failed = 0;

	check(result, testVariableDeclaration(), "Variable Declaration Tests");
	check(result, testArithmeticOperations(), "Arithmetic Operations Tests");
	check(result, testBooleanExpressions(), "Boolean Expressions Tests");
	check(result, testControlFlow(), "Control Flow Tests");
	check(result, testLoops(), "Loops Tests");
	check(result, testDataStructures(), "Data Structures Tests");
	check(result, testFunctions(), "Functions Tests");
	check(result, testNodeFamily(), "Node Family Tests");
	check(result, testGotoStatement(), "Goto Statement Tests");
	check(result, testUserInput(), "User Input Tests");
	check(result, testConsoleOutput(), "Console Output Tests");
	check(result, testErrorHandling(), "Error Handling Tests");

    return result;
}