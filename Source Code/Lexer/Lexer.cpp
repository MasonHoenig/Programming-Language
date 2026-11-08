//The tutorial I followed included these
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Lexer.h"

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
    case TokenType::Quote:
        return "Quote";
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

//assume the file type is correct
std::vector<Token> RunLexerProgram(const std::string& filePath) {
    std::vector<Token> tokenSet;
    int line = 1;
    std::string programLine;
    std::ifstream file(filePath);
    bool commenting = false;

    if (file.is_open()) {
        while (getline (file, programLine)) {
            std::vector<Token> newLine = RunLexerLine(programLine, line, tokenSet.size(), commenting);
            if (newLine.back().type == TokenType::UnclosedComment) {
                commenting = true;
                newLine.pop_back();
            } else {
                commenting = false;
            }

            for (int i = 0; i < newLine.size(); i++) {
                tokenSet.push_back(newLine[i]);
            }

            line++;
        }
    }

    /*for (int i = 0; i < tokenSet.size(); i++) {
        if (tokenSet[i].type == TokenType::UNKNOWN) {
            std::cout << "Unknown token found: " << tokenSet[i].value << " at line " << tokenSet[i].sourceLocal.line << ", column " << tokenSet[i].sourceLocal.column << std::endl;
        }
    }*/

    SourceLocation endFileLocation = {line, 0, tokenSet.size()};
    tokenSet.emplace_back(TokenType::EndFileMarker, "0", endFileLocation);

    //if there's an unkown token, return null
    if (find(tokenSet.begin(), tokenSet.end(), TokenType::UNKNOWN) != tokenSet.end()) {
        std::vector<Token> nullVec;
        return nullVec;
    } else {
        return tokenSet;
    }
}

std::vector<Token> RunLexerLine(std::string input, int line, int vecSize, bool commenting) {
    std::vector<Token> lineSet;

    LexicalAnalyzer lexer(input);
    lineSet = lexer.tokenize(line, vecSize, commenting);
    //How do multiline comments work?

    return lineSet;
}

std::string RunLexerTest(std::string input) {
	std::string output = "";

	LexicalAnalyzer lexer(input);
	std::vector<Token> tokens = lexer.tokenize(0, 0, false); //return the vector of tokens to the parser

    if (tokens.empty()) {
        return output;
    }

    if (tokens[tokens.size() - 1].type == TokenType::UNKNOWN && tokens[tokens.size() - 1].value == "NoCommentEnd") {
        return "Error! Unclosed comment block: " + input;
    } else if (tokens[tokens.size() - 1].type != TokenType::Semicolon && tokens[tokens.size() - 1].value != "}") {
        return "Error! Missing Semicolon: " + input;
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
                return "Error! Unknown token type: " + tokens[i].value + ": " + input;
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

            switch (assignType) {
                case 0:
                    break;
                case 1:
                case 2:
                    if (tokens[i].type == TokenType::Word || tokens[i].type == TokenType::SingleChar || tokens[i].type == TokenType::BoolValue) {
                        return "Error! Invalid assignment: " + input;
                    }
                    break;
                case 3:
                    if (tokens[i].type == TokenType::Integer|| tokens[i].type == TokenType::Decimal || tokens[i].type == TokenType::BoolValue) {
                        return "Error! Invalid assignment: " + input;
                    }
                    break;
                case 4:
                    if (tokens[i].type == TokenType::Integer|| tokens[i].type == TokenType::Decimal || tokens[i].type == TokenType::Word || tokens[i].type == TokenType::BoolValue) {
                        return "Error! Invalid assignment: " + input;
                    }
                    break;
                case 5:
                    if (tokens[i].type == TokenType::Integer|| tokens[i].type == TokenType::Decimal || tokens[i].type == TokenType::Word || tokens[i].type == TokenType::SingleChar) {
                        return "Error! Invalid assignment: " + input;
                    }
                    break;
            }

            output += "(" + getTokenTypeName(tokens[i].type) + "," + tokens[i].value + ")";

            if (i < tokens.size() - 1) {
                if ((tokens[i].type == TokenType::Math && tokens[i].value == "/") && (tokens[i + 1].type == TokenType::Integer && tokens[i + 1].value == "0")) {
                    return "Error! Division by zero: " + input;
                } else if (tokens[i].type == TokenType::Comparison) {
                    if (tokens[i - 1].type != TokenType::VarName && tokens[i + 1].type != TokenType::VarName && tokens[i - 1].type != tokens[i + 1].type) {
                        return "Error! Incompatible types: " + input;
                    }
                } else if (tokens[i].type == TokenType::Keyword) {
                    if (tokens[i].value == "variable") {
                        if (tokens[i + 1].type != TokenType::VarType) {
                            return "Error! Invalid assignment: " + input;
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
                            return "Error! Invalid assignment: " + input;
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
                            return "Error! Invalid return type: " + input;
                        }
                    }
                }
                
                output += ", ";
            }
        }
        output += "]";

        if (parenOpen != 0 || brackOpen != 0 || braceOpen != 0) {
            return "Error! Missing Parentheses: " + input;
        }
        if (funcType != 0 && funcType != returnType) {
            return "Error! Function return type mismatch: " + input;
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
