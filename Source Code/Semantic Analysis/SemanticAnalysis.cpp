#include "SemanticAnalysis.h";

bool variableDec(VariableDeclaration* node, SemAnalysis sA) {
    std::string decT = node->varType;
    std::string name = node->identifier;
    LiteralExpression* lE = dynamic_cast<LiteralExpression*>(node);
    TokenType actT = lE->type;
    
    if(decT == "number") {
        if(actT != TokenType::Integer) {
            sA.isFalse();
            return sA.Analysis();
        }
    }
    else if(decT == "decimal") {
        if(actT != TokenType::Decimal) {
            sA.isFalse();
            return sA.Analysis();
        }
    }
    else if(decT == "word") {
        if(actT != TokenType::Word) {
            sA.isFalse();
            return sA.Analysis();
        }
    }
    else if(decT == "boolean") {
        if(actT != TokenType::BoolValue) {
            sA.isFalse();
            return sA.Analysis();
        }
    }

    std::vector<std::string> scope = sA.scope();
    for(int i = 0; i < scope.size();i++)
    {
        if(scope.at(i) == name)
        {
            sA.isFalse();
            return sA.Analysis();
        }
    }
    scope.push_back(name);

    return sA.Analysis();
}


bool SemTests(Program* node, SemAnalysis sA){
    Statement* s = node->declarations.front();
    VariableDeclaration* vD = dynamic_cast<VariableDeclaration*>(s);
    bool check = variableDec(vD, sA);

    return true;
}

bool runSemTests(Program* node) {
    SemAnalysis sA = SemAnalysis(node);
    return SemTests(node, sA);
}


//final output the ASTNode tree and a symbol table (vectors)
SemAnalysis SemanticAnalaysis(Program* node) {
    SemAnalysis sA = SemAnalysis(node);

    SemTests(node, sA);

    return sA;
}