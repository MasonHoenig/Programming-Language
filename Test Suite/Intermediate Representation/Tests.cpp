// An example test suite file
#include "../Run_Tests.h"
#include "../../Source Code/Intermediate Representation/IR.cpp"

/*
* So, This will take some form of AST (Abstract Syntax Tree) and output C++ Code that can be passed to Clang.
* The IR usually outputs Assembly code, but we don't know enough assembly,so we are outputting to a Three address code for the Emitter to make into C++
* Takes AST as input and then "flattens" it. This "flat" AST might(?) be a Three Address Code
* A TAC list might look like ([*,a,b],[uminus,b,t1],[jump,L1,NULL])
* Jumps in TAC
* Unconditional jump: jump,dest,NULL
* Conditional jump: jump,dest,Pointer_to_conditional_TAC
*/
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.
testReturn irTests(){
    testReturn passFail; //Initialize the passFail struct
    passFail.passed = 0;
    passFail.failed = 0;
    //passFail.errorMessages.push_back(""); //Add an empty string to the error vector.
    
    std::vector<Program> testInputs = 
    {
        "testInput1",
        "testInput2"
    };
    std::vector<TAC> expectedOutputs = 
    {
        "testOutput1",
        "testOutput2"
    };
    std::vector<std::string> errorMessages = 
    {
        "testErr1",
        "testErr2"
    };
    std::vector<TAC> realOutputs; //This is what stores the actual outputs from the functions running

    //Actual function execution goes here, unfortunately there is no way to make it flexible.

    //End function execution

    //The number of test inputs and outputs are hardcoded, so its feasable(though bad practice) to hardcode the number of loops
    for (int i = 0; i < testInputs.size() || i < expectedOutputs.size(); i++){
        
    }

    return passFail;
}