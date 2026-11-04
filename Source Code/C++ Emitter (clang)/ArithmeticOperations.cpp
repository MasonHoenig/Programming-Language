#include "TacToCpp.h"

#include <charconv>
#include <string>
#include <type_traits>
#include <variant>
#include <ostream>

using namespace tac_helpers;

bool tac_helpers::emitArithmetic(const Instr& instr, std::ostream& output, std::string& errorMessage) {
	if (instr.type != Type::Number && instr.type != Type::Decimal) {
		errorMessage = "Arithmetic operations are only supported for Number and Decimal types";
		return false;
	}

	for (const Operand* operand : { &instr.a, &instr.b }) {
		if (std::holds_alternative<StrLit>(*operand) || std::holds_alternative<bool>(*operand)) {
			errorMessage = "Arithmetic operations are not supported for String or Boolean types";
			return false;
		}
		if (!std::holds_alternative<int>(*operand) &&
			!std::holds_alternative<double>(*operand) &&
			!std::holds_alternative<Var>(*operand)) {
			errorMessage = "Arithmetic instruction is missing an operand";
			return false;
		}
	}

	if (instr.type == Type::Number && (std::holds_alternative<double>(instr.a) || std::holds_alternative<double>(instr.b))) {
		errorMessage = "Cannot perform arithmetic on Number type with Decimal operands";
		return false;
	}

	if (instr.operand == Operator::Divide || instr.operand == Operator::Mod) {
		auto* integer = std::get_if<int>(&instr.b);
		auto* floatingPoint = std::get_if<double>(&instr.b);
		if ((integer && *integer == 0) || (floatingPoint && *floatingPoint == 0.0)) {
			errorMessage = "Division or Modulus by zero is not allowed";
			return false;
		}
	}

	const bool decimal = instr.type == Type::Decimal;
	if (decimal && instr.operand == Operator::Mod) {
		errorMessage = "Modulus operation is not supported for Decimal type";
		return false;
	}

	std::string a = operandToCpp(instr.a);
	std::string b = operandToCpp(instr.b);

	const char* symbol = nullptr;
	switch (instr.operand) {
	case Operator::Add: symbol = " + "; break;
	case Operator::Subtract: symbol = " - "; break;
	case Operator::Multiply: symbol = " * "; break;
	case Operator::Divide: symbol = " / "; break;
	case Operator::Mod: symbol = " % "	; break;
	default:
		errorMessage = "Unsupported arithmetic operation";
		return false;
	}

	std::string x = operandToCpp(instr.a);
	if (decimal && !std::holds_alternative<double>(instr.a)) {
		x = "static_cast<double>(" + x + ")";
	}

	output << "    " << instr.dest << " = " << x  << symbol << operandToCpp(instr.b) << ";\n";
	return true;
}