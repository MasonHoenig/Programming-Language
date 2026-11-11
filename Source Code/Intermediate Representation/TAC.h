//Put classes and structs that need to be used by other parts of the program here
#ifndef IR_HEADER
#define IR_HEADER
#include <string>
/*  TAC is short for Three Address Code
 *   Specifically, it takes 3 strings: operand, arg1, arg2
 *   operand values look like: * + - / uminus jmp
 *   arg1 is NEVER null, and is usually defined as some variable or a pointer to a previous result
 *   arg2 is SOMETIMES null, and is defined as a variable or a pointer to a previous result
 *   if statements are a special case of jmp and look like: jmp, (pointer to Label), (pointer to boolean expression)
 *   strings are structured like: =, (pointer to beginnging of string), (number of characters in string)
 */
struct TAC
{
    std::string operand = "";
    std::string arg1 = "";
    std::string arg2 = "";
};

#endif