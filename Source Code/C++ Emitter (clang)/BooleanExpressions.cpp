#include "TacToCpp.h"

#include <string>
#include <variant>
#include <ostream>

using namespace tac_helpers;

bool tac_helpers::emitBoolExpressions(const Instr& instr, std::ostream& output, std::string& errorMessage) {
	if(instr.type != Type::Number && instr.type != Type::Boolean && instr.type != Type::Decimal) {
		errorMessage = "Invalid type for boolean expression";
		return false;
	}

	for (const Operand* operand : { &instr.a, &instr.b }) {
		if (!std::holds_alternative<int>(*operand) &&
			!std::holds_alternative<double>(*operand) &&
			!std::holds_alternative<Var>(*operand)) {
			errorMessage = "Comparison instruction is missing an operand";
			return false;
		}
	}

	std::string a = operandToCpp(instr.a);
	std::string b = operandToCpp(instr.b);

	const char* symbol = nullptr;
	switch (instr.operand) {
		case Operator::GreaterThan: symbol = " > "; break;
		case Operator::LessThan: symbol = " < "; break;
		case Operator::EqualTo: symbol = " == "; break;
		case Operator::GreaterThanOrEqualTo: symbol = " >= "; break;
		case Operator::LessThanOrEqualTo: symbol = " <= "; break;
		case Operator::NotEqualTo: symbol = " != "; break;
		case Operator::And: symbol = " && "; break;
		case Operator::Or: symbol = " || "; break;
		case Operator::Xor:
			output << "    " << instr.dest << " = (!" << a << ") != (!" << b << ");\n";
			return true;
		default:
			errorMessage = "Unsupported comparison operation";
			return false;
	}

	output << "    " << instr.dest << " = " << a << symbol << b << ";\n";

	return true;
}