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
    std::unordered_map<std::string, TokenType> boolTypes = {{"true", TokenType::BoolValue}, {"false", TokenType::BoolValue}};

    void initKeywords() {
        keywords["variable"] = TokenType::Keyword;
        keywords["function"] = TokenType::Keyword;
        keywords["return"] = TokenType::Keyword;
        keywords["if"] = TokenType::Keyword;
        keywords["else"] = TokenType::Keyword;
        keywords["while"] = TokenType::Keyword;
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
                    return returnPos + 2; // Return position after the closing */
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
                if (position + 1 < input.length() && input[position + 1] == '=') {
                    tokens.emplace_back(TokenType::Comparison, "==");
                    position += 2;
                } else {
                    tokens.emplace_back(TokenType::Assign, std::string(1, currentChar));
                    position++;
                }
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
};