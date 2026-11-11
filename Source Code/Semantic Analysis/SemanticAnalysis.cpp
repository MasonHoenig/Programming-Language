#include "SemanticAnalysis.h";

bool variableDec(VariableDeclaration* node) {
    std::string decT = node->varType;
    LiteralExpression* lE = dynamic_cast<LiteralExpression*>(node);
    TokenType actT = lE->type;

    

    return true;
}


bool SemTests(Program node, int size){

    for(int i = 0; i < size;i++){
        Statement* s = node.declarations.at(i);
        VariableDeclaration* vD = dynamic_cast<VariableDeclaration*>(s);
        bool check = variableDec(vD);
    }

    return true;
}



std::string runSemTest(ASTNode input) {

   
    return "";
}

//final output the ASTNode tree and a symbol table (vectors)