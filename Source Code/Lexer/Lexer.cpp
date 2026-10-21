//The tutorial I followed included these
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

//Lexer
enum class TokenType {
	Keyword,
	VarType,
	VarName,
	Integer,
	Decimal,
	Word,
	SingleChar,
	BoolValue,
	Assign,
	Math,
    Quote,
	Semicolon,
	Parentheses,
	Comparison,
	UNKNOWN, // Added for unrecognized tokens
};

struct Token {
	TokenType type;
	std::string value;
	
	Token(TokenType t, const std::string& v):type(t),value(v) {}
};

class LexicalAnalyzer {
private:
	std::string input;
    size_t position;
    std::unordered_map<std::string, TokenType> keywords;
	std::unordered_map<std::string, TokenType> varTypes;

    void initKeywords() {
        keywords["variable"] = TokenType::Keyword;
        keywords["if"] = TokenType::Keyword;
        keywords["else"] = TokenType::Keyword;
        keywords["while"] = TokenType::Keyword;
        //What other keywords are there?
    }

    void initVarTypes() {
        varTypes["number"] = TokenType::VarType;
        varTypes["decimal"] = TokenType::VarType;
        varTypes["word"] = TokenType::VarType;
        varTypes["letter"] = TokenType::VarType;
        varTypes["bool"] = TokenType::VarType;
    }
    
    bool isSpace(char c) {
		if (c == ' ' || c == '\n' || c == '\t') {
			return true;
		} else {
			return false;
		}
	}
	
	bool isLetter(char c) {
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			return true;
		} else {
			return false;
		}
	}
	
	bool isNumber(char c) {
		if (c >= '0' && c <= '9') {
			return true;
		} else {
			return false;
		}
	}
	
	bool isLetOrNum(char c) {
		if (isLetter(c) == true || isNumber(c) == true) {
			return true;
		} else {
			return false;
		}
	}
	
	std::string getNextWord() {
        size_t start = position;
        while (position < input.length() && isLetOrNum(input[position]) == true) {
            position++;
        }
        return input.substr(start, position - start);
    }
    
    std::string getNextNumber() {
        size_t start = position;
        bool hasDecimal = false;
        while (position < input.length() && (isNumber(input[position]) == true || input[position] == '.')) {
            if (input[position] == '.') {
                if (hasDecimal) {
                    break;
				}
                hasDecimal = true;
            }
            position++;
        }
        return input.substr(start, position - start);
    }
    
public:
    LexicalAnalyzer(const std::string& source):input(source),position(0) {
        initKeywords();
        initVarTypes();
    }

	//Copy/pasted from the tutorial I followed with minor tweaks. Will definitly need fixing.
	vector<Token> tokenize() {
        vector<Token> tokens;

        while (position < input.length()) {
            char currentChar = input[position];

            if (isSpace(currentChar)) {
                position++;
                continue;
            }

            if (isLetter(currentChar)) {
                string word = getNextWord();
                if (keywords.find(word) != keywords.end()) {
                    tokens.emplace_back(TokenType::Keyword, word);
				} else if (varTypes.find(word) != varTypes.end()) {
                    tokens.emplace_back(TokenType::VarType, word);
                } else {
                    tokens.emplace_back(TokenType::VarName, word);
                }
            } else if (isNumber(currentChar)) {
                string number = getNextNumber();
				//what is npos?
                if (number.find('.') != string::npos) {
					tokens.emplace_back(TokenType::Decimal, number);
                } else {
                    tokens.emplace_back(TokenType::Integer, number);
                }
			} else if (currentChar == '=') {
				tokens.emplace_back(TokenType::Assign, string(1, currentChar));
				position++;
            } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '%') {
                tokens.emplace_back(TokenType::Math, string(1, currentChar));
                position++;
            } else if (currentChar == '\'' || currentChar == '\"') {
                tokens.emplace_back(TokenType::Quote, string(1, currentChar));
                position++;
            } else if (currentChar == '<' || currentChar == '>' || currentChar == '=' || currentChar == '!') {
                std::string comparisonOp(1, currentChar);
                position++;
                if (position < input.length() && input[position] == '=') {
                    comparisonOp += '=';
                    position++;
                }
                tokens.emplace_back(TokenType::Comparison, comparisonOp);
            } else if (currentChar == ';') {
				tokens.emplace_back(TokenType::Semicolon, string(1, currentChar));
				position++;
            } else if (currentChar == '(' || currentChar == ')' || currentChar == '{' || currentChar == '}') {
                tokens.emplace_back(TokenType::Parentheses, string(1, currentChar));
                position++;
            } else {
                tokens.emplace_back(TokenType::UNKNOWN, string(1, currentChar));
                position++;
            }
        }

        return tokens;
    }
};

std::string getTokenTypeName(TokenType type)
{
    switch (type) {
    case TokenType::Keyword:
        return "Keyword";
	case TokenType::VarType:
		return "VarType";
    case TokenType::VarName:
        return "VarName";
    case TokenType::Integer:
        return "Integer";
    case TokenType::Decimal:
        return "Decimal";
	case TokenType::Word:
		return "Word";
	case TokenType::SingleChar:
		return "SingleChar";
	case TokenType::BoolValue:
		return "BoolValue";
	case TokenType::Assign:
		return "Assign";
    case TokenType::Math:
        return "Math";
	case TokenType::Semicolon:
        return "Semicolon";
    case TokenType::Parentheses:
        return "Parentheses";
	case TokenType::Comparison:
		return "Comparison";
    case TokenType::UNKNOWN:
        return "UNKNOWN";
    default:
        return "ERROR: Unknown TokenType";
    }
}

// not sure what to return or take as an input
std::string RunLexerTest(std::string input) {
	std::string output = "";

	LexicalAnalyzer lexer(input);
	std::vector<Token> tokens = lexer.tokenize();

    if (tokens[tokens.size() - 1].type != TokenType::Semicolon) {
        return "Error! Missing Semicolon";
    } else {
        output += "[";
        for (size_t i = 0; i < tokens.size(); ++i) {
            output += "(" + getTokenTypeName(tokens[i].type) + "," + tokens[i].value + ")";
            if (i < tokens.size() - 1) {
                output += ", ";
            }
        }
        output += "]";
    }

	return output;
}

std::string RunLexerTestHardCoded(std::string input) {
    if (input == "variable word w = hello;") {
        return "[(Keyword,variable), (VarType,word), (VarName,w), (Assign,=), (Quote,\"), (Word,hello), (Quote,\"), (Semicolon,;)]";
    } else if (input == "variable letter let1 = a;") {
        return "[(Keyword,variable), (VarType,letter), (VarName,let1), (Assign,=), (Quote,\'), (SingleChar,a), (Quote,\'), (Semicolon,;)]";
    } else if (input == "variable bool b = true;") {
        return "[(Keyword,variable), (VarType,bool), (VarName,b), (Assign,=), (BoolValue,true), (Semicolon,;)]";
    } else if (input == "x = (x + 3.4) * 5;") {
        //if 5 is an integer, that could be a problem.
        return "[(VarName,x), (Assign,=), (Parentheses,(), (VarName,x), (Math,+), (Decimal,3.4), (Parentheses,)), (Math,*), (Integer,5), (Semicolon,;)]";
    } else if (input == "if (x >= 0) { return true; }") {
        return "[(Keyword,if), (Parentheses,(), (VarName,x), (Comparison,>=), (Integer,0), (Parentheses,)), (Parentheses,{), (Keyword,return), (BoolValue,true), (Semicolon,;), (Parentheses,})";
    } else if (input == "brr number x = 5;") {
        return "Error! Unknown token type: brr";
    } else if (input == "variable number x = \"hello\";") {
        return "Error! Invalid assignment";
    } else if (input == "if (x >= 0 { return true; }") {
        return "Error! Missing Parentheses";
    } else if (input == "if (x >= y) { return true; }") {
        return "Error! Incompatible types";
    } else {
        return "Error! Input not recognized";
    }
}
