//The tutorial I followed included these
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Lexer.h"

//Lexer, moved to Lexer.h, but leaving this here just in case
/*enum class TokenType {
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
    std::unordered_map<std::string, TokenType> boolTypes = {{"true", TokenType::BoolValue}, {"false", TokenType::BoolValue}};

    void initKeywords() {
        keywords["variable"] = TokenType::Keyword;
        keywords["function"] = TokenType::Keyword;
        keywords["return"] = TokenType::Keyword;
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
        varTypes["void"] = TokenType::VarType; //only for functions
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

    int GetCommentEndPos(int startPos) {
        int returnPos = startPos + 2;

        if (returnPos >= input.length()) {
            return -1; // Invalid comment
        } else {
            while (returnPos < input.length() - 1) {
                if (input[returnPos] == '*' && input[returnPos + 1] == '/') {
                    return returnPos + 2; // Return position after the closing comment
                }
            }
        }
        
        return -1;
    }
    
public:
    LexicalAnalyzer(const std::string& source):input(source),position(0) {
        initKeywords();
        initVarTypes();
    }

	//Copy/pasted from the tutorial I followed with minor tweaks. Will definitly need fixing.
	std::vector<Token> tokenize() {
        std::vector<Token> tokens;

        while (position < input.length()) {
            char currentChar = input[position];

            if (isSpace(currentChar)) {
                position++;
                continue;
            }

            //comments
            if (position + 1 < input.length() && currentChar == '/') {
                if (input[position + 1] == '/') {
                    break; //stops reading the input
                } else if (input[position + 1] == '*') {
                    position = GetCommentEndPos(position);
                    if (position == -1) {
                        tokens.emplace_back(TokenType::UNKNOWN, "NoCommentEnd");
                        break;
                    } else if (position >= input.length()) {
                        break; //stops reading the input
                    }
                }
            }

            if (isLetter(currentChar)) {
                std::string word = getNextWord();
                if (keywords.find(word) != keywords.end()) {
                    tokens.emplace_back(TokenType::Keyword, word);
				} else if (varTypes.find(word) != varTypes.end()) {
                    tokens.emplace_back(TokenType::VarType, word);
                } else if (boolTypes.find(word) != boolTypes.end()) {
                    tokens.emplace_back(TokenType::BoolValue, word);
                } else {
                    tokens.emplace_back(TokenType::VarName, word);
                }
            } else if (isNumber(currentChar)) {
                std::string number = getNextNumber();
				//what is npos?
                if (number.find('.') != std::string::npos) {
					tokens.emplace_back(TokenType::Decimal, number);
                } else {
                    tokens.emplace_back(TokenType::Integer, number);
                }
            } else if (currentChar == '=') {
				tokens.emplace_back(TokenType::Assign, std::string(1, currentChar));
				position++;
            } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '%') {
                tokens.emplace_back(TokenType::Math, std::string(1, currentChar));
                position++;
            } else if (currentChar == '\'' || currentChar == '\"') {
                tokens.emplace_back(TokenType::Quote, std::string(1, currentChar));
                position++;
            // PROBLEM: == won't be checked
            } else if (currentChar == '<' || currentChar == '>' || currentChar == '=' || currentChar == '!') { 
                std::string comparisonOp(1, currentChar);
                position++;
                if (position < input.length() && input[position] == '=') {
                    comparisonOp += '=';
                    position++;
                }
                tokens.emplace_back(TokenType::Comparison, comparisonOp);
            } else if (currentChar == ';') {
				tokens.emplace_back(TokenType::Semicolon, std::string(1, currentChar));
				position++;
            } else if (currentChar == '(' || currentChar == ')' || currentChar == '{' || currentChar == '}' || currentChar == '[' || currentChar == ']') {
                tokens.emplace_back(TokenType::Parentheses, std::string(1, currentChar));
                position++;
            } else {
                tokens.emplace_back(TokenType::UNKNOWN, std::string(1, currentChar));
                position++;
            }
        }

        return tokens;
    }
};*/

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

std::string RunLexerTest(std::string input) {
	std::string output = "";

	LexicalAnalyzer lexer(input);
	std::vector<Token> tokens = lexer.tokenize(); //return the vector of tokens to the parser

    if (tokens[tokens.size() - 1].type == TokenType::UNKNOWN && tokens[tokens.size() - 1].value == "NoCommentEnd") {
        return "Error! Unclosed comment block";
    } else if (tokens[tokens.size() - 1].type != TokenType::Semicolon || tokens[tokens.size() - 1].value != "}") {
        return "Error! Missing Semicolon";
    } else {
        int parenOpen = 0;
        int brackOpen = 0;
        int braceOpen = 0;

        int assignType = 0;
        int funcType = 0;
        int returnType = 0;

        output += "[";
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i].type == TokenType::UNKNOWN) {
                return "Error! Unknown token type: " + tokens[i].value;
            }

            if (tokens[i].type == TokenType::Parentheses && tokens[i].value == "(") {
                parenOpen++;
            } else if (tokens[i].type == TokenType::Parentheses && tokens[i].value == ")") {
                parenOpen--;
            } else if (tokens[i].type == TokenType::Parentheses && tokens[i].value == "[") {
                brackOpen++;
            } else if (tokens[i].type == TokenType::Parentheses && tokens[i].value == "]") {
                brackOpen--;
            } else if (tokens[i].type == TokenType::Parentheses && tokens[i].value == "{") {
                braceOpen++;
            } else if (tokens[i].type == TokenType::Parentheses && tokens[i].value == "}") {
                braceOpen--;
            }

            output += "(" + getTokenTypeName(tokens[i].type) + "," + tokens[i].value + ")";

            if (i < tokens.size() - 1) {
                if ((tokens[i].type == TokenType::Math && tokens[i].value == "/") && (tokens[i + 1].type == TokenType::Integer && tokens[i + 1].value == "0")) {
                    return "Error! Division by zero";
                } else if (tokens[i].type == TokenType::Comparison) {
                    if ((tokens[i - 1].type != TokenType::VarName || tokens[i + 1].type != TokenType::VarName) && tokens[i - 1].type != tokens[i + 1].type) {
                        return "Error! Incompatible types";
                    }
                } else if (tokens[i].type == TokenType::Keyword) {
                    if (tokens[i].value == "variable") {
                         if (tokens[i + 1].type != TokenType::VarType) {
                            return "Error! Invalid assignment";
                        } else if (tokens[i + 1].value == "number") {
                            assignType = 1;
                        } else if (tokens[i + 1].value == "decimal") {
                            assignType = 2;
                        } else if (tokens[i + 1].value == "word") {
                            assignType = 3;
                        } else if (tokens[i + 1].value == "letter") {
                            assignType = 4;
                        } else if (tokens[i + 1].value == "bool") {
                            assignType = 5;
                        }
                    } else if (tokens[i].value == "function") {
                        if (tokens[i + 1].type != TokenType::VarType) {
                            return "Error! Invalid assignment";
                        } else if (tokens[i + 1].value == "number") {
                            funcType = 1;
                        } else if (tokens[i + 1].value == "decimal") {
                            funcType = 2;
                        } else if (tokens[i + 1].value == "word") {
                            funcType = 3;
                        } else if (tokens[i + 1].value == "letter") {
                            funcType = 4;
                        } else if (tokens[i + 1].value == "bool") {
                            funcType = 5;
                        }
                    } else if (tokens[i].value == "return") {
                        if (tokens[i + 1].type == TokenType::VarName) {
                            returnType = assignType;
                        } else if (tokens[i + 1].type == TokenType::Integer) {
                            returnType = 1;
                        } else if (tokens[i + 1].type == TokenType::Decimal) {
                            returnType = 2;
                        } else if (tokens[i + 1].type == TokenType::Word) {
                            returnType = 3;
                        } else if (tokens[i + 1].type == TokenType::SingleChar) {
                            returnType = 4;
                        } else if (tokens[i + 1].type == TokenType::BoolValue) {
                            returnType = 5;
                        } else {
                            return "Error! Invalid return type";
                        }
                    }
                }
                
                output += ", ";
            }
        }
        output += "]";

        if (parenOpen != 0 || brackOpen != 0 || braceOpen != 0) {
            return "Error! Missing Parentheses";
        }
        if (funcType != 0 && funcType != returnType) {
            return "Error! Function return type mismatch";
        }
    }

	return output;
}

std::string RunLexerTestHardCoded(std::string input) {
    if (input == "variable number x = 1;") {
        return "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (Integer,1), (Semicolon,;)]";
    } else if (input == "variable word w = \"hello\";") {
        return "[(Keyword,variable), (VarType,word), (VarName,w), (Assign,=), (Quote,\"), (Word,hello), (Quote,\"), (Semicolon,;)]";
    } else if (input == "variable letter let1 = 'a';") {
        return "[(Keyword,variable), (VarType,letter), (VarName,let1), (Assign,=), (Quote,\'), (SingleChar,a), (Quote,\'), (Semicolon,;)]";
    } else if (input == "variable bool b = true;") {
        return "[(Keyword,variable), (VarType,bool), (VarName,b), (Assign,=), (BoolValue,true), (Semicolon,;)]";
    } else if (input == "x = (x + 3.4) * 5;") {
        //if 5 is an integer, that could be a problem.
        return "[(VarName,x), (Assign,=), (Parentheses,(), (VarName,x), (Math,+), (Decimal,3.4), (Parentheses,)), (Math,*), (Integer,5), (Semicolon,;)]";
    } else if (input == "if (x >= 0) { return true; }") {
        return "[(Keyword,if), (Parentheses,(), (VarName,x), (Comparison,>=), (Integer,0), (Parentheses,)), (Parentheses,{), (Keyword,return), (BoolValue,true), (Semicolon,;), (Parentheses,})]";
    } else if (input == "variable number x = 1; // This is a comment") {
        return "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (Integer,1), (Semicolon,;)]";
    } else if (input == "variable number x = y /* alread defined */ + 1;") {
        return "[(Keyword,variable), (VarType,number), (VarName,x), (Assign,=), (VarName,y), (Math,+), (Integer,1), (Semicolon,;)]";
    } else if (input == "variable number x = y /* alread defined + 1;") {
        return "Error! Unclosed comment block";
    } else if (input == "variable number x = 1") {
        return "Error! Missing Semicolon";
    } else if (input == "brr number x = 5;") {
        return "Error! Unknown token type: brr";
    } else if (input == "variable number x = \"hello\";") {
        return "Error! Invalid assignment";
    } else if (input == "if (x >= 0 { return true; }") {
        return "Error! Missing Parentheses";
    } else if (input == "if (\"hello\" >= 0) { return true; }") {
        return "Error! Incompatible types";
    } else if (input == "function number func() { string x = \"hello\"; return x; }") {
        return "Error! Function return type mismatch";
    } else if (input == "variable decimal d = 3.14 / 0;") {
        return "Error! Division by zero";
    } else if (input == "variable number x = arr[5];") {
        return "Error! Array index out of bounds";
    } else {
        return "Error! Input not recognized";
    }
}
