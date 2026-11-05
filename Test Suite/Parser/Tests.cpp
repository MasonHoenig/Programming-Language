// An example test suite file
#include "../Run_Tests.h"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.

//-----Test 1----- 
// Source Code = x=1;
void test1(int &passed, int &failed, std::vector<std::string> &errors){
    // Call Parser script with above input and compare output with expected output above, update global vars
    std::string expectedOutput = R"(Program
└── VariableDeclaration
    ├── Type: number
    ├── Identifier: x
    └── Initializer: LiteralExpression
        └── Value: 1)";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 1 (Number Declaration) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 2----- 
// Source Code = variable word z = "hello world!";
void test2(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── VariableDeclaration
    ├── Type: word
    ├── Identifier: z
    └── Initializer: LiteralExpression
        └── Value: "hello world!")";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 2 (Word Declaration) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 3----- 
// Source Code = variable number a = x + y * 2;
void test3(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── VariableDeclaration
    ├── Type: number
    ├── Identifier: a
    └── Initializer: BinaryExpression
        ├── Left: IdentifierExpression (x)
        ├── Operator: +
        └── Right: BinaryExpression
            ├── Left: IdentifierExpression (y)
            ├── Operator: *
            └── Right: LiteralExpression (2))";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 3 (Operator Precedence) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 4----- 
// Source Code = if (health > 5) { x = 1; }
void test4(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── IfStatement
    ├── Condition: BinaryExpression
    │   ├── Left: IdentifierExpression (health)
    │   ├── Operator: >
    │   └── Right: LiteralExpression (5)
    └── ThenBranch: 
        └── BinaryExpression
            ├── Left: IdentifierExpression (x)
            ├── Operator: =
            └── Right: LiteralExpression (1))";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 4 (If Statement) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 5----- 
// Source Code = while (x < 5) { x = x + 1; }
void test5(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── WhileLoop
    ├── Condition: BinaryExpression
    │   ├── Left: IdentifierExpression (x)
    │   ├── Operator: <
    │   └── Right: LiteralExpression (5)
    └── Body: 
        └── BinaryExpression
            ├── Left: IdentifierExpression (x)
            ├── Operator: =
            └── Right: BinaryExpression
                ├── Left: IdentifierExpression (x)
                ├── Operator: +
                └── Right: LiteralExpression (1))";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 5 (While Loop) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 6----- 
// Source Code = Node Castle { OptionSet { Option("Wait") -> Goto Castle; } }
void test6(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── NodeDeclaration: Castle
    └── Body:
        └── OptionSetStatement
            └── OptionStatement
                ├── DisplayText: LiteralExpression ("Wait")
                └── Transition: GotoStatement (Castle))";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 6 (Node and OptionSet) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 7----- 
// Source Code = variable array number arr[3] = [2, 3, 4];
void test7(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── ArrayDeclaration
    ├── Type: number
    ├── Identifier: arr
    ├── Size: LiteralExpression (3)
    └── Elements:
        ├── LiteralExpression (2)
        ├── LiteralExpression (3)
        └── LiteralExpression (4))";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 7 (Arrays) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 8----- 
// Source Code = function void execute() { print("test"); }
void test8(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── FunctionDeclaration
    ├── ReturnType: void
    ├── Name: execute
    ├── Parameters: None
    └── Body:
        └── FunctionCallExpression
            ├── Name: print
            └── Arguments:
                └── LiteralExpression ("test"))";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 8 (Functions) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 9----- 
// Source Code = for (variable number y = 0, y < 5, y = y + 1) { print(y); }
void test9(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── ForLoop
    ├── Initialization: VariableDeclaration
    │   ├── Type: number
    │   ├── Identifier: y
    │   └── Initializer: LiteralExpression (0)
    ├── Condition: BinaryExpression
    │   ├── Left: IdentifierExpression (y)
    │   ├── Operator: <
    │   └── Right: LiteralExpression (5)
    ├── Update: BinaryExpression
    │   ├── Left: IdentifierExpression (y)
    │   ├── Operator: =
    │   └── Right: BinaryExpression
    │       ├── Left: IdentifierExpression (y)
    │       ├── Operator: +
    │       └── Right: LiteralExpression (1)
    └── Body:
        └── FunctionCallExpression
            ├── Name: print
            └── Arguments:
                └── IdentifierExpression (y))";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 9 (For Loops) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

//-----Test 10----- 
// Source Code = if (not true and x == 1) { }
void test10(int &passed, int &failed, std::vector<std::string> &errors){
    std::string expectedOutput = R"(Program
└── IfStatement
    ├── Condition: BinaryExpression
    │   ├── Left: UnaryExpression
    │   │   ├── Operator: not
    │   │   └── Right: LiteralExpression (true)
    │   ├── Operator: and
    │   └── Right: BinaryExpression
    │       ├── Left: IdentifierExpression (x)
    │       ├── Operator: ==
    │       └── Right: LiteralExpression (1)
    └── ThenBranch: Empty)";

    std::string actualOutput = "Placeholder"; // Replace with myParser.PrintTree(tree)
    std::string error = "Parser Test 10 (Logic) output does not match";

    if (expectedOutput == actualOutput){
        passed += 1;
    } else {
        failed += 1;
        errors.push_back(error);
    }

}

testReturn parserTests(){ // This function is called and returns the struct. I will call each test as a function and use global vars to return

    int passed = 0;
    int failed = 0;
    std::vector<std::string> errors = {};

    test1(passed,failed,errors);
    test2(passed,failed,errors);
    test3(passed,failed,errors);
    test4(passed,failed,errors);
    test5(passed,failed,errors);
    test6(passed,failed,errors);
    test7(passed,failed,errors);
    test8(passed,failed,errors);
    test9(passed,failed,errors);
    test10(passed,failed,errors);

    testReturn passFail; 
    passFail.passed = passed;
    passFail.failed = failed;
    passFail.errorMessages = errors;
    return passFail;
}