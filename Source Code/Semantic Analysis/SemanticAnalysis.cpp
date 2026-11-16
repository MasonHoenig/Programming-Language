#include "SemanticAnalysis.h";

bool variableDec(VariableDeclaration* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
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

    if(scope.empty())
    {
        std::unordered_map<std::string, std::string> sMap;
        sMap[name] = decT;
        scope.push(sMap);
    }
    else
    {
        std::unordered_map<std::string, std::string> sMap = scope.top();
        if(sMap.count(name)){
            sA.isFalse();
            return sA.Analysis();
        }
        sMap[name] = decT;
    }

    return sA.Analysis();
}

bool ifState(IfStatement* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}

bool whileLp(WhileLoop* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}

bool GotoState(GotoStatement* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}

bool optionState(OptionStatement* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}

bool optionSetState(OptionSetStatement* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}

bool nodeDec(NodeDeclaration* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}


bool SemTests(Program* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope){
    bool check;

    std::vector<Statement*> nv = node->declarations;
    for(int i = 0; i < nv.size();i++)
    {
        Statement* s = nv.at(i);
        if(VariableDeclaration* vD = dynamic_cast<VariableDeclaration*>(s))
        {
            check = variableDec(vD, sA, scope);
        }
        else if(IfStatement* iS = dynamic_cast<IfStatement*>(s))
        {
            check = ifState(iS, sA, scope);
        }
        else if(WhileLoop* wL = dynamic_cast<WhileLoop*>(s))
        {
            check = whileLp(wL, sA, scope);
        }
        else if(GotoStatement* gTS = dynamic_cast<GotoStatement*>(s))
        {
            check = GotoState(gTS, sA, scope);
        }
        else if(OptionStatement* oS = dynamic_cast<OptionStatement*>(s))
        {
            check = optionState(oS, sA, scope);
        }
        else if(OptionSetStatement* oSS = dynamic_cast<OptionSetStatement*>(s))
        {
            check = optionSetState(oSS, sA, scope);
        }
        else if(NodeDeclaration* nD = dynamic_cast<NodeDeclaration*>(s))
        {
            check = nodeDec(nD, sA, scope);
        }
    }

    return check;
}

bool runSemTests(Program* node) {
    SemAnalysis sA = SemAnalysis(node);
    std::stack<std::unordered_map<std::string, std::string>> S = sA.Sc();
    return SemTests(node, sA, S);
}


//final output the ASTNode tree and a symbol table (vectors)
SemAnalysis SemanticAnalaysis(Program* node) {
    SemAnalysis sA = SemAnalysis(node);
    std::stack<std::unordered_map<std::string, std::string>> S = sA.Sc();

    SemTests(node, sA, S);

    return sA;
}