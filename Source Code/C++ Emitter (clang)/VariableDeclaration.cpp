#include "TacToCpp.h"

#include <cctype>
#include <string>
#include <cstdio>

std::string variableDeclaration(const TAC& tac) {
	std::string valueType;
	std::string rhs = tac.arg2;

	auto source = types.find(tac.arg2);
	if (source != types.end()) {
		valueType = source->second;
		rhs = names[tac.arg2];
	}
	else if (tac.arg2.size() >= 2 && tac.arg2.front() == '"' && tac.arg2.back() == '"') {
		valueType = "std::string";
		std::string inner = tac.arg2.substr(1, tac.arg2.size() - 2);
		rhs = "\"" + escapeForCpp(inner) + "\"";
	}
	else if (isBoolean(tac.arg2)) 
		valueType = "bool";
	else if (isInteger(tac.arg2)) 
		valueType = "int";
	else if (isDouble(tac.arg2))  
		valueType = "double";
	else 
		return "Error: unknown value '" + tac.arg2 + "'\n";

	// Assign t0, t1, t2, etc. to values with no identifier in TAC
	auto varNames = types.find(tac.arg1);
	if (varNames == types.end()) {
		std::string cppName = (tac.operand == "=str")
			? "t" + std::to_string(nextId++)
			: tac.arg1;
		names[tac.arg1] = cppName;
		types[tac.arg1] = valueType;
		return declOrAssign(valueType, cppName) + " = " + rhs + ";\n";
	}

	const std::string& declared = varNames->second;
	bool valid = (declared == valueType) || (declared == "double" && valueType == "int");
	if (!valid)
		return "Error: cannot assign to '" + tac.arg1 + "' (type mismatch)\n";

	return names[tac.arg1] + " = " + rhs + ";\n";
}