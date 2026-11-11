#include "IR.h"

/*Statement* findStatementType(Statement* statement){
    //I don't see a partucularly elegant way to do this, so its time for a massive block of dyamic cast attempts
    /*
    * types:
    * VariableDeclaration
    * IfStatement
    * WhileLoop
    * ArrayDeclaration
    * FunctionDeclaration
    * ForLoop
    * Not doing Swine Specific statements yet
    */ /*

    VariableDeclaration* varDec = dynamic_cast<VariableDeclaration*>(statement);
    if (varDec)
    {
        return varDec; 
    }
    IfStatement* ifState = dynamic_cast<IfStatement*>(statement);
    if (ifState)
    {
        return ifState;
    }
    WhileLoop* whiLoop = dynamic_cast<WhileLoop*>(statement);
    if(whiLoop)
    {
        return whiLoop;
    }
    ArrayDeclaration* arrDec = dynamic_cast<ArrayDeclaration*>(statement);
    if(arrDec)
    {
        return arrDec;
    }
    FunctionDeclaration* funDec = dynamic_cast<FunctionDeclaration*>(statement);
    if(funDec)
    {
        return funDec;
    }
    ForLoop* forLp = dynamic_cast<ForLoop*>(statement);
    if(forLp)
    {
        return forLp;
    }
    //If it is not any of these, return nullptr
    return nullptr;
}*/



//Outputs a vector<vector<TAC>>
std::vector<std::vector<TAC>> Create_IR(Program* program){

    int statementNum = 0; //Increment every time there is a vector<TAC> added to the ouput vector
    int exprNum = 0; //Increment every time there is a TAC added to the inner vector
    std::vector<std::vector<TAC>> output;
    std::vector<TAC> threeAddressCodes; //Contains every Three address code for a statement. Needs to be cleared after each statement.

    for (auto* statement : program->declarations){
        //Determine what statement type it is somehow?
        //auto* typedStatement = findStatementType(statement);
        statementNum++;
        VariableDeclaration *varDec = dynamic_cast<VariableDeclaration *>(statement);
        if (varDec)
        {
            // process into a TAC and skip to next loop (continue)
            exprNum++;
            int startExpr = exprNum;
            threeAddressCodes.push_back(handleExpression(varDec->initializer,&exprNum).threeAddressCode);

            exprNum++;
            threeAddressCodes.push_back(
                {
                    "=",
                    varDec->identifier,
                    //pointerToString(varDec->initializer) // Not correct, needs to point to another address in the threeAdressCodes vector
                    //std::to_string(startExpr)
                    handleExpression(varDec->initializer,&exprNum).value
                }
            );

            output.push_back(threeAddressCodes);
            threeAddressCodes.clear();

            continue;    
        }
        IfStatement *ifState = dynamic_cast<IfStatement *>(statement);
        if (ifState)
        {
            // process into a TAC and skip to next loop (continue)

            continue;
        }
        WhileLoop *whiLoop = dynamic_cast<WhileLoop *>(statement);
        if (whiLoop)
        {
            // process into a TAC and skip to next loop (continue)

            continue;
        }
        ArrayDeclaration *arrDec = dynamic_cast<ArrayDeclaration *>(statement);
        if (arrDec)
        {
            // process into a TAC and skip to next loop (continue)

            continue;
        }
        FunctionDeclaration *funDec = dynamic_cast<FunctionDeclaration *>(statement);
        if (funDec)
        {
            // process into a TAC and skip to next loop (continue)

            continue;
        }
        ForLoop *forLp = dynamic_cast<ForLoop *>(statement);
        if (forLp)
        {
            // process into a TAC and skip to next loop (continue)

            continue;
        }
        // Throw error: unerecognised statement type
        std::cerr << "Error, Unrecognised Statement type given to IR." << std::endl;
        exit(EXIT_FAILURE);

    }
    return output;
}