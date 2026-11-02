// An example test suite file
#include "../Run_Tests.h"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.

int passed = 0;
int failed = 0;


/*void driverTest(){
    if (expectedOuput == currentOutput){
        passed += 1;
    } else {
    failed += 1;
    }
} */

void syntaxErrorTest(){ // missing semi colon
    std::string input = R"(
    int main(){
        int x = 5
        return 0
         }
    )";
}

void runtimeErrorTest(){ // tests for segmentation error, pointer location does not exist
    std::string input = R"(
    int main(){
        int*ptr = nullptr;
        *ptr = 10;
        return 0
         }
    )";
}


void sematicErrorTest(){ // tests for type mismatch
    std::string input = R"(
    int main(){
        int y = "hello";
        return 0
         }
    )";
}





testReturn driverTests(){
    testReturn passFail; //If you come up with a better name, feel free to change it.
    passFail.passed = 1;
    passFail.failed = 0;


    if (failed > 0) {
    passFail.errorMessages.push_back("A test or more failed."); 
    std::cout << passFail.passed;
    std::cout << passFail.failed;
    }
    return passFail;
}