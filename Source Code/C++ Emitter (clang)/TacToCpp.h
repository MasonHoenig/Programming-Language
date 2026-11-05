#pragma once

#include <optional>
#include <string>
#include <variant>
#include <vector>

enum class Type { Number, Decimal, Text, Boolean };

struct Var { std::string name; };
struct StrLit { 
	std::string value; 
	explicit StrLit(std::string val) : value(std::move(val)) {}
};
using Operand = std::variant<std::monostate, Var, int, double, bool, StrLit>;

enum class Operator { 
	Decl, 
	Copy, 
	Add,
	Subtract,
	Multiply,
	Divide,
	Mod, 
	GreaterThan,
	LessThan,
	EqualTo,
	GreaterThanOrEqualTo,
	LessThanOrEqualTo,
	NotEqualTo,
	Or,
	And,
	Xor,
	Label, 
	Jump, 
	JumpIfFalse }; 

struct Instr {
	Operator operand;
	std::string dest;
	Operand a{};
	Operand b{};
	Type type = Type::Number;
};

inline Operand make_operand() { return std::monostate{}; }
inline Operand make_operand(int v) { return v; }
inline Operand make_operand(double v) { return v; }
inline Operand make_operand(bool v) { return v; }
inline Operand make_operand(Var v) { return v; }
inline Operand make_operand(StrLit v) { return v; }
inline Operand make_operand(std::string v) { return StrLit{ std::move(v) }; }
inline Operand make_operand(const char* v) { return StrLit{ std::string(v) }; }

using TAC = std::vector<Instr>;

struct EmitResult {
	bool success = false;
	std::string code;
	std::string errorMessage;
};

class TacToCpp {
public:
	EmitResult emit(const TAC* tac) const;
	EmitResult emit(const std::optional<TAC>& tac) const;
};

namespace tac_helpers {
	std::string escape(const std::string& string);
	std::string operandToCpp(const Operand& operand);
	const char* cppType(Type type);
	bool hasValue(const Operand& operand);

	template <typename EmitterFunc>
	inline std::string WriteCpp(const Instr& instr, EmitterFunc emitter) {
		std::ostringstream output;
		std::string errorMessage;
		if (emitter(instr, output, errorMessage)) {
			return output.str();
		}
		return "Error: " + errorMessage + "\n";
	}

	bool emitDeclaration(const Instr& instr, std::ostream& output, std::string errorMessage);
	bool emitArithmetic(const Instr& instr, std::ostream& output, std::string& errorMessage);
	bool emitBoolExpressions(const Instr& instr, std::ostream& output, std::string& errorMessage);
}