#ifndef TESTS_HEADER
#define TESTS_HEADER
    #include <iostream> //I also decided to add some common includes into the header protection to prevent bloating. Maybe overkill for tests but hey.
    #include <string>
    #include <vector>
    struct testReturn{ // Structs are just C++'s way of allowing function to return multiple values. In this case, I just needed it to return two separate ints and a vector.
        int passed; //The number of tests passed
        int failed; // The number of tests failed
        std::vector<std::string> errorMessages;
    };
#endif