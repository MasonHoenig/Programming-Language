#include "../Parser/AST.h"
#include "TAC.h"
#include <sstream>

// Put IR-specific classes and structs here.


//Struct for handling Expressions, because they are set up really weirdly
struct ExpressionHandlerOutput
{
    TAC threeAddressCode;
    std::string value = NULL;
    std::string type = NULL;
};


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

ExpressionHandlerOutput handleExpression(Expression* expr,int* exprCounter){

    ExpressionHandlerOutput output;
    //Dynamic cast block part 2: electric boogaloo

    LiteralExpression* litExp = dynamic_cast<LiteralExpression *>(expr);
    if (litExp)
    {
        exprCounter++;

        output.value = litExp->value;
        //output.type = litExp->type;

        return output;
    }
    IdentifierExpression *idExp = dynamic_cast<IdentifierExpression *>(expr);
    if (idExp)
    {
        exprCounter++;
        // Somehow needs to reference the result of a different calulation. Update: Function now has the runing exprCounter variable for this.

        return output;
    }
    BinaryExpression *binExp = dynamic_cast<BinaryExpression *>(expr);
    if (binExp)
    {
        exprCounter++;
        // recursively call to the left and right of the operand
        output =
        {
            "",//An empty string, because TokenType was used incorrectly to define the operator, otherwise it would be this: binExp->op
            handleExpression(binExp->left,exprCounter).value,
            handleExpression(binExp->right,exprCounter).value
        };
        return output;
    }
    UnaryExpression *unExp = dynamic_cast<UnaryExpression *>(expr);
    if (unExp)
    {
        exprCounter++;
        // TAC = {op,val1,NULL}
        output =
        {
            "",//Once again an empty string, because TokenType was used incorrectly to define the operator, otherwise it would be this: unExp->op
            handleExpression(unExp->right,exprCounter).value
            //The third value stays NULL
        };
        return output;
    }
    FunctionCallExpression *funCallExp = dynamic_cast<FunctionCallExpression *>(expr);
    if (funCallExp)
    {
        exprCounter++;
        // Process the expression into TAC
        output =
        {
            "",
            "",
        };
        return output;
    }
    ArrayAccessExpression *arrAccExp = dynamic_cast<ArrayAccessExpression *>(expr);
    if (arrAccExp)
    {
        exprCounter++;
        // Process the expression into TAC
        output =
        {
            "",
            "",

        };
        return output;
    }
    std::cerr << "Error: Unrecognised Expression given to handleExpression" << std::endl;
    exit(EXIT_FAILURE);
}