//Put classes and structs that need to be used by other parts of the program here
#ifndef IR_HEADER
#define IR_HEADER
#include <string>
// TAC is short for Three Address Code
struct TAC
{
    std::string operand;
    std::string arg1;
    std::string arg2;
};

#endif