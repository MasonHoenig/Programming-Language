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
    EndFileMarker,
    UnclosedComment, //Added so the Lexer can read multiline comments properly
	UNKNOWN, // Added for unrecognized tokens
};

struct SourceLocation {
    int line;
    int column;
    int offset;
};

struct Token {
	TokenType type;
	std::string value;
    SourceLocation sourceLocal;
	
	Token(TokenType t, const std::string& v):type(t),value(v) {}
    //Token(TokenType t, const std::string& v, SourceLocation sl):type(t),value(v),sourceLocal(sl) {}
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
        keywords["for"] = TokenType::Keyword;
        keywords["print"] = TokenType::Keyword;
        keywords["Node"] = TokenType::Keyword;
        keywords["OptionSet"] = TokenType::Keyword;
        keywords["Option"] = TokenType::Keyword;
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
                returnPos++;
            }
        }
        
        return -1;
    }


    bool IsExistingVar(std::vector<Token> tokens, std::string name) {
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i].type == TokenType::VarName && tokens[i].value == name) {
                return true;
            }
        }

        return false;
    }

    /*Token rewriteToVarName(Token var) {
        
        return var;
    }*/
    
public:
    LexicalAnalyzer(const std::string& source):input(source),position(0) {
        initKeywords();
        initVarTypes();
    }

	std::vector<Token> tokenize(int line, int vecSize, bool commenting) {
        std::vector<Token> tokens;
        bool isEquation = false;
        SourceLocation newSL = {line, 0, vecSize};

        if (commenting == true) {
            position = GetCommentEndPos(0);
            if (position == -1) {
                tokens.emplace_back(TokenType::UnclosedComment, "", newSL);
                return tokens;
            }
        }

        while (position < input.length()) {
            newSL.column = position;
            newSL.offset = vecSize + tokens.size();
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
                        newSL.column = input.size();
                        tokens.emplace_back(TokenType::UnclosedComment, "", newSL);
                        break;
                    } else if (position >= input.length()) {
                        break; //stops reading the input
                    }
                    currentChar = input[position];
                    if (isSpace(currentChar)) {
                        position++;
                        continue;
                    }
                }
            }

            if (isLetter(currentChar)) {
                std::string word = getNextWord();
                if (keywords.find(word) != keywords.end()) {
                    tokens.emplace_back(TokenType::Keyword, word, newSL);
				} else if (varTypes.find(word) != varTypes.end()) {
                    tokens.emplace_back(TokenType::VarType, word, newSL);
                } else if (boolTypes.find(word) != boolTypes.end()) {
                    tokens.emplace_back(TokenType::BoolValue, word, newSL);
                } else if ((tokens.size() > 0 && (tokens.back().type == TokenType::VarType || tokens.back().type == TokenType::Comparison)) || (isEquation && tokens.back().type != TokenType::Quote)) {
                    tokens.emplace_back(TokenType::VarName, word, newSL);
                } else if (tokens.size() > 0 && tokens.back().type == TokenType::Quote) {
                    if (word.length() == 1) {
                        tokens.emplace_back(TokenType::SingleChar, word, newSL);
                    } else {
                        tokens.emplace_back(TokenType::Word, word, newSL);
                    }
                } else {
                    if (IsExistingVar(tokens, word)) {
                        tokens.emplace_back(TokenType::VarName, word, newSL);
                    } else {
                        tokens.emplace_back(TokenType::UNKNOWN, word, newSL);
                        std::cout << "Unknown token found: " << tokens.back().value << " at line " << tokens.back().sourceLocal.line << ", column " << tokens.back().sourceLocal.column << std::endl;
                    }
                }
            } else if (isNumber(currentChar)) {
                std::string number = getNextNumber();
				//what is npos?
                if (number.find('.') != std::string::npos) {
					tokens.emplace_back(TokenType::Decimal, number, newSL);
                } else {
                    tokens.emplace_back(TokenType::Integer, number, newSL);
                }
            } else if (currentChar == '=') {
                if (position + 1 < input.length() && input[position + 1] == '=') {
                    if (tokens.size() > 0 && tokens.back().type == TokenType::UNKNOWN) {
                        Token rewrite = tokens.back();
                        tokens.pop_back();
                        rewrite.type = TokenType::VarName;
                        tokens.emplace_back(rewrite);
                    }
                    tokens.emplace_back(TokenType::Comparison, "==", newSL);
                    position += 2;
                } else {
                    if (tokens.size() == 1 && tokens.back().type == TokenType::UNKNOWN) {
                        Token rewrite = tokens.back();
                        tokens.pop_back();
                        rewrite.type = TokenType::VarName;
                        tokens.emplace_back(rewrite);
                    }
                    tokens.emplace_back(TokenType::Assign, std::string(1, currentChar), newSL);
                    position++;
                    isEquation = true;
                }
            } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '%') {
                tokens.emplace_back(TokenType::Math, std::string(1, currentChar), newSL);
                position++;
            } else if (currentChar == '\'' || currentChar == '\"') {
                tokens.emplace_back(TokenType::Quote, std::string(1, currentChar), newSL);
                position++;
            } else if (currentChar == '<' || currentChar == '>' || currentChar == '!') { 
                std::string comparisonOp(1, currentChar);
                position++;
                if (position < input.length() && input[position] == '=') {
                    comparisonOp += '=';
                    position++;
                }
                if (tokens.size() > 0 && tokens.back().type == TokenType::UNKNOWN) {
                    Token rewrite = tokens.back();
                    tokens.pop_back();
                    rewrite.type = TokenType::VarName;
                    tokens.emplace_back(rewrite);
                }
                tokens.emplace_back(TokenType::Comparison, comparisonOp, newSL);
            } else if (currentChar == ';') {
				tokens.emplace_back(TokenType::Semicolon, std::string(1, currentChar), newSL);
				position++;
            } else if (currentChar == '(' || currentChar == ')' || currentChar == '{' || currentChar == '}' || currentChar == '[' || currentChar == ']') {
                tokens.emplace_back(TokenType::Parentheses, std::string(1, currentChar), newSL);
                position++;
            } else {
                tokens.emplace_back(TokenType::UNKNOWN, std::string(1, currentChar), newSL);
                position++;
            }
        }

        return tokens;
    }
};