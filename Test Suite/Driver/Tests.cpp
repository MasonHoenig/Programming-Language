// An example test suite file
#include "../Run_Tests.h"
// Return the number of tests passed and failed. All error reporting should be handled by adding the error message to the provided vector.
testReturn driverTests(){
    testReturn passFail; //If you come up with a better name, feel free to change it.
    passFail.passed = 1;
    passFail.failed = 0;
    passFail.errorMessages.push_back(""); //Add an empty string to the error vector.
    return passFail;
}