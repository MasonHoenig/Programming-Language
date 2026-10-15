// The code for including and running the test suites goes here.
// This file HOPEFULLY shouldn't need to be modified, but you never know.

#include "C++ Emitter (clang)/Tests.cpp"
#include "Driver/Tests.cpp"
#include "Intermediate Representation/Tests.cpp"
#include "Lexer/Tests.cpp"
#include "Parser/Tests.cpp"
#include "Semantic Analysis/Tests.cpp"

void runTests(){
    testReturn testArray[6];

    //These are in alphabetical order, but if execution order makes more sense then we can change it.
    std::cout << "Running Emitter Tests." << std::endl;
    testArray[0] = emitterTests();
    std::cout << "Tests completed successfully." << std::endl;
    std::cout << "Tests passed: " << testArray[0].passed << std::endl;
    std::cout << "Tests failed: " << testArray[0].failed << std::endl;
    std::cout << "Error messages:" << std::endl;
    for(const auto& message : testArray[0].errorMessages)
    {
        std::cout << message << std::endl;
    }
    std::cout << "______________________________" << std::endl;

    std::cout << "Running Driver Tests." << std::endl;
    testArray[1] = driverTests();
    std::cout << "Tests passed: " << testArray[1].passed << std::endl;
    std::cout << "Tests failed: " << testArray[1].failed << std::endl;
    std::cout << "Error messages:" << std::endl;
    for (const auto &message : testArray[0].errorMessages)
    {
        std::cout << message << std::endl;
    }
    std::cout << "______________________________" << std::endl;

    std::cout << "Running Intermediate Representation Tests." << std::endl;
    testArray[2] = irTests();
    std::cout << "Tests passed: " << testArray[2].passed << std::endl;
    std::cout << "Tests failed: " << testArray[2].failed << std::endl;
    std::cout << "Error messages:" << std::endl;
    for (const auto &message : testArray[0].errorMessages)
    {
        std::cout << message << std::endl;
    }
    std::cout << "______________________________" << std::endl;

    std::cout << "Running Lexer Tests." << std::endl;
    testArray[3] = lexerTests();
    std::cout << "Tests passed: " << testArray[3].passed << std::endl;
    std::cout << "Tests failed: " << testArray[3].failed << std::endl;
    std::cout << "Error messages:" << std::endl;
    for (const auto &message : testArray[0].errorMessages)
    {
        std::cout << message << std::endl;
    }
    std::cout << "______________________________" << std::endl;

    std::cout << "Running Parser Tests." << std::endl;
    testArray[4] = parserTests();
    std::cout << "Tests passed: " << testArray[4].passed << std::endl;
    std::cout << "Tests failed: " << testArray[4].failed << std::endl;
    std::cout << "Error messages:" << std::endl;
    for (const auto &message : testArray[0].errorMessages)
    {
        std::cout << message << std::endl;
    }
    std::cout << "______________________________" << std::endl;

    std::cout << "Running Semantic Analysis Tests." << std::endl;
    testArray[5] = semanticTests();
    std::cout << "Tests passed: " << testArray[5].passed << std::endl;
    std::cout << "Tests failed: " << testArray[5].failed << std::endl;
    std::cout << "Error messages:" << std::endl;
    for (const auto &message : testArray[0].errorMessages)
    {
        std::cout << message << std::endl;
    }
    std::cout << "______________________________" << std::endl;
    //I forgot how annoying working with cout is in C++

    int totalPassed = 0;
    int totalFailed = 0;
        for (testReturn result : testArray){
        totalPassed += result.passed;

        if(result.failed > 0){
            totalFailed += result.failed;
        }
    }
    std::cout << "______________________________" << std::endl;
    std::cout << "Total tests passed: " << totalPassed << std::endl;
    std::cout << "Total tests failed: " << totalFailed << std::endl;
}

int main(){
    runTests();
}