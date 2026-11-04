#include "TacToCpp.h"
#include <iostream>
#include <sstream>
#include <string>

int main() {
	// At the top of main write all includes automatically - user is not expected to write them manually
    
    // instead of hard coded values, insert TAC.operand, TAC.arg1, TAC.arg2
    // Then output of IR will be inserted directly into converter

	using namespace  tac_helpers;

    // ----- Variable Declaration Example -----
    Instr variableDeclaration{ Operator::Decl, "result", make_operand("This is an example text"),{}, Type::Text };
    std::cout << tac_helpers::WriteCpp(variableDeclaration, tac_helpers::emitDeclaration);

    // ----- Arithmetic Example -----
    Instr arithmetic{ Operator::Add, "x", make_operand(2), make_operand(3), Type::Number };
    std::cout << tac_helpers::WriteCpp(arithmetic, tac_helpers::emitArithmetic);

    // ----- Boolean Expressions Example -----
	Instr booleanExpressions{ Operator::GreaterThan, "result", make_operand(5), make_operand(3), Type::Boolean };
    std::cout << tac_helpers::WriteCpp(booleanExpressions, tac_helpers::emitBoolExpressions);

    return 0; 
    // At the end of main write an exit code automatically, user is not expected to write it manually
}