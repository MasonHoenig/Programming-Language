#include "TacToCpp.h"

#include <cctype>
#include <string>
#include <cstdio>

// ----- Helper Functions -----

static bool isInteger(const std::string& str) {
	size_t i = (!str.empty() && (str[0] == '-' || str[0] == '+')) ? 1 : 0;
	if (i >= str.size()) return false;
	for (; i < str.size(); ++i)
		if (!std::isdigit(static_cast<unsigned char>(str[i]))) return false;
	return true;
}

static bool isDouble(const std::string& str) {
	size_t i = (!str.empty() && (str[0] == '-' || str[0] == '+')) ? 1 : 0;
	bool seenDot = false, seenDigit = false;
	for (; i < str.size(); ++i) {
		if (str[i] == '.') {
			if (seenDot) return false;
			seenDot = true;
		}
		else if (std::isdigit(static_cast<unsigned char>(str[i]))) seenDigit = true;
		else return false;
	}
	return seenDot && seenDigit;
}

static bool isBoolean(const std::string& str) {
	return str == "true" || str == "false";
}

static std::string escapeForCpp(const std::string& s)
{
	std::string out;
	out.reserve(s.size());
	for (unsigned char c : s)
	{
		switch (c)
		{
		case '\\': out += "\\\\"; break;
		case '"':  out += "\\\""; break;
		case '\n': out += "\\n";  break;
		case '\r': out += "\\r";  break;
		case '\t': out += "\\t";  break;
		case '\0': out += "\\0";  break;
		default:
			if (c < 32 || c == 127)
			{
				char buf[8];
				snprintf(buf, sizeof(buf), "\\x%02x", c);
				out += buf;
			}
			else out += c;
		}
	}
	return out;
}

// ----------------------------

std::string VariableDeclaration::variableDeclaration(const TAC& instr) {
	std::string valType;
	std::string rhs = instr.arg2;

	if (instr.operand == "=str") {
		valType = "std::string";
		rhs = "\"" + escapeForCpp(instr.arg2) + "\"";
	}
	else if (instr.operand == "=") {
		auto src = types.find(instr.arg2);
		if (src != types.end()) {
			valType = src->second;
			rhs = names[instr.arg2];
		}
		else if (instr.arg2.size() >= 2 && instr.arg2.front() == '"' && instr.arg2.back() == '"') {		//-------------------
			valType = "std::string";
			std::string inner = instr.arg2.substr(1, instr.arg2.size() - 2);							// This checks for string without // "=str"
			rhs = "\"" + escapeForCpp(inner) + "\"";
		}																								//-------------------
		else if (isBoolean(instr.arg2)) valType = "bool";
		else if (isInteger(instr.arg2)) valType = "int";
		else if (isDouble(instr.arg2))  valType = "double";
		else return "Error: unknown value '" + instr.arg2 + "'\n";
	}
	else return "Error: Unsupported operation: " + instr.operand + "\n";

	auto it = types.find(instr.arg1);
	if (it == types.end()) {
		std::string cppName = (instr.operand == "=str")
			? "t" + std::to_string(nextId++)
			: instr.arg1;
		names[instr.arg1] = cppName;
		types[instr.arg1] = valType;
		return valType + " " + cppName + " = " + rhs + ";\n";
	}

	const std::string& declared = it->second;
	bool valid = (declared == valType) || (declared == "double" && valType == "int");
	if (!valid)
		return "Error: cannot assign to '" + instr.arg1 + "' (type mismatch)\n";

	return names[instr.arg1] + " = " + rhs + ";\n";
}