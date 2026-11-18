#include "SemanticAnalysis.h";

bool compareTType(std::string dT, TokenType aT) {
    if(dT == "number") {
        if(aT != TokenType::Integer) {
            return false;
        }
    }
    else if(dT == "decimal") {
        if(aT != TokenType::Decimal) {
            return false;
        }
    }
    else if(dT == "word") {
        if(aT != TokenType::Word) {
            return false;
        }
    }
    else if(dT == "boolean") {
        if(aT != TokenType::BoolValue) {
            return false;
        }
    }
    return true;
}

bool bExpCheck(BinaryExpression* b, std::stack<std::unordered_map<std::string, std::string>> scope){
    TokenType lTType;
    std::string lType;
    TokenType rTType;
    std::string rType;

    //getting left side type
    if(LiteralExpression* l = dynamic_cast<LiteralExpression*>(b->left)){
        lTType = l-> type;
    }
    else if(IdentifierExpression* l = dynamic_cast<IdentifierExpression*>(b->left)){
        if(scope.empty())
        {
            return false;
        }
        else
        {
            std::unordered_map<std::string, std::string> sMap = scope.top();
            if(!sMap.count(l->name)){
                return false;
            }
            else
            {
                lType = sMap[l->name];
            }
        }
    }
    else if(BinaryExpression* l = dynamic_cast<BinaryExpression*>(b->left)){
        if(bExpCheck(l, scope)) {} else {return false;}
    }

    //getting right side type
    if(LiteralExpression* r = dynamic_cast<LiteralExpression*>(b->right)){
        rTType = r-> type;
    }
    else if(IdentifierExpression* r = dynamic_cast<IdentifierExpression*>(b->right)){
        if(scope.empty())
        {
            return false;
        }
        else
        {
            std::unordered_map<std::string, std::string> sMap = scope.top();
            if(!sMap.count(r->name)){
                return false;
            }
            else
            {
                rType = sMap[r->name];
            }
        }
    }
    else if(BinaryExpression* r = dynamic_cast<BinaryExpression*>(b->right)){
        if(bExpCheck(r, scope)) {} else {return false;}
    }

    //comparing types
    if(lTType == TokenType::UNKNOWN) //assuming UNKNOWN is empty
    {
        if(rTType == TokenType::UNKNOWN)
        {
            if(lType == rType)
            {
                return true;
            }
        }
        else
        {
            return compareTType(lType, rTType);
        }
    }
    else
    {
        if(rTType == TokenType::UNKNOWN)
        {
            return compareTType(rType, lTType);
        }
        else
        {
            if(lTType == rTType)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}


bool variableDec(VariableDeclaration* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    std::string decT = node->varType;
    std::string name = node->identifier;

    if(LiteralExpression* lE = dynamic_cast<LiteralExpression*>(node))
    {
        TokenType actT = lE->type;
        
        if(!compareTType(decT, actT)) {
            sA.isFalse();
            return sA.Analysis();
        }
    }

    if(BinaryExpression* bE = dynamic_cast<BinaryExpression*>(node))
    {
        if(!bExpCheck(bE, scope))
        {
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
    //Expression* e = node->condition;
    BinaryExpression* bE = dynamic_cast<BinaryExpression*>(node);
    std::vector<Statement*> b = node->body;

    //compare while loop statement
    IdentifierExpression* l = dynamic_cast<IdentifierExpression*>(bE->left);
    LiteralExpression* r = dynamic_cast<LiteralExpression*>(bE->right);
    TokenType rType = r->type;
    std::string lType;

    if(scope.empty())
    {
        sA.isFalse();
        return sA.Analysis();
    }
    else
    {
        std::unordered_map<std::string, std::string> sMap = scope.top();
        if(!sMap.count(l->name)){
            sA.isFalse();
            return sA.Analysis();
        }
        else
        {
            lType = sMap[l->name];
        }
    }
    
    if(compareTType(lType, rType)) {}
    else{
        sA.isFalse();
        return sA.Analysis();
    }

    //compare body
    std::unordered_map<std::string, std::string> sMap;
    scope.push(sMap);

    return SemTests(b, sA, scope);
}

bool GotoState(GotoStatement* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}

bool optionState(OptionStatement* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}

bool optionSetState(OptionSetStatement* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}

bool nodeDec(NodeDeclaration* node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope) {
    
}


bool SemTests(std::vector<Statement*> node, SemAnalysis sA, std::stack<std::unordered_map<std::string, std::string>> scope){
    bool check;

    for(int i = 0; i < node.size();i++)
    {
        Statement* s = node.at(i);
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
    std::vector<Statement*> nv = node->declarations;

    return SemTests(nv, sA, S);
}

//final output the ASTNode tree and a symbol table (vectors)
SemAnalysis SemanticAnalaysis(Program* node) {
    SemAnalysis sA = SemAnalysis(node);
    std::stack<std::unordered_map<std::string, std::string>> S = sA.Sc();
    std::vector<Statement*> nv = node->declarations;

    SemTests(nv, sA, S);

    return sA;
}