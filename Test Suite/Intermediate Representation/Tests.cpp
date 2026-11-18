//The test suite file for the IR/Code Generation
#include "../Run_Tests.h"
#include "../../Source Code/Intermediate Representation/CodeGeneration.cpp"

//Make a dedicated function to test each AST Polymorphic class type first and foremost.

//Statement Tests
void testVariableDeclaration(Program *program, std::vector<std::string> *errors,testReturn* passFail)
{
    //Initialize the declarations vector state to represent the test state.
    VariableDeclaration *varDecl = new VariableDeclaration();
    varDecl->varType = "number";
    varDecl->identifier = "x";

    LiteralExpression *literal1 = new LiteralExpression();
    literal1->value = "5";
    literal1->type = TokenType::Integer;

    varDecl->initializer = literal1;

    program->declarations.push_back(varDecl);

    //Set up the expected output string:
    std::string expectedOutput = "int x = 5;";

    //Call the function(s) from the real code.
    std::string realOutput = GenerateCode(program);

    //Compare output.
    if (expectedOutput == realOutput)
    {
        passFail->passed++;
    }else{
        passFail->failed++;
        passFail->errorMessages.push_back("Error when testing VariableDeclaration. Expected: " + expectedOutput + " Got: " + realOutput + "\n");
    }

    //Clean up declarations vector for the next function to use.
    program->declarations.clear();
}
void testIfStatement(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testWhileLoop(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testArrayDeclaration(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testFunctionDeclaration(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testForLoop(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}

//Expression Tests

void testLiteralExpression(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testIdentifierExpression(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testBinaryExpression(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testUnaryExpression(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testFunctionCallExpression(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}
void testArrayAccessExpression(Program *program, std::vector<std::string> *errors, testReturn *passFail)
{
    // Unimplemented, do not call
    std::cerr << "Unimplemented tests should not be called.";
    exit(EXIT_FAILURE);
}

/*
* So, This will take some form of AST (Abstract Syntax Tree) and output C++ Code that can be passed to Clang.
*/
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.
testReturn irTests(){
    testReturn passFail; //Initialize the passFail struct
    passFail.passed = 0;
    passFail.failed = 0;
    
   //std::vector<std::string> errorMessages;
    Program* testInput = new Program();
    // Actual function execution goes here.
    testVariableDeclaration(testInput,&passFail.errorMessages,&passFail);
    
    //End function execution

    /*for (int i = 0; i < testInputs.size() || i < expectedOutputs.size(); i++){

        if(expectedOutputs[i] == realOutputs[i]){
            passFail.passed++;
        }else{passFail.failed++;}
    }*/
    
    return passFail;
}
