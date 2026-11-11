#include "../Parser/AST.h"
#include "TAC.h"
#include <sstream>

// Put IR-specific classes and structs here.

/*
 * Helper functions:
 * Pointer to string conversion
 *
 */

template <typename T>
// Converts a pointer into strings for insertion into a TAC
std::string pointerToString(T* ptr)
{
    std::ostringstream oss;
    oss << ptr;

    std::string output = oss.str();
    return output;
}

/*
 * Runnable Functions
 * handleExpressions
 * probably going to make a handleStatements function too at some point
 */

TAC handleExpression(Expression* expr){

    TAC output;
    //Dynamic cast block part 2: electric boogaloo
    LiteralExpression* litExp = dynamic_cast<LiteralExpression *>(expr);
    if (litExp)
    {
        //Process the expression into TAC
            output = 
            {
                "Operand",
                "val1",
                "val2"
            };
        return output;
    }
    IdentifierExpression *idExp = dynamic_cast<IdentifierExpression *>(expr);
    if (idExp)
    {
        // Process the expression into TAC

        return output;
    }
    BinaryExpression *binExp = dynamic_cast<BinaryExpression *>(expr);
    if (binExp)
    {
        // Process the expression into TAC

        return output;
    }
    UnaryExpression *unExp = dynamic_cast<UnaryExpression *>(expr);
    if (unExp)
    {
        // Process the expression into TAC

        return output;
    }
    FunctionCallExpression *funCallExp = dynamic_cast<FunctionCallExpression *>(expr);
    if (funCallExp)
    {
        // Process the expression into TAC

        return output;
    }
    ArrayAccessExpression *arrAccExp = dynamic_cast<ArrayAccessExpression *>(expr);
    if (arrAccExp)
    {
        // Process the expression into TAC

        return output;
    }
    std::cerr << "Error: Unrecognised Expression given to handleExpression" << std::endl;
    exit(EXIT_FAILURE);
}