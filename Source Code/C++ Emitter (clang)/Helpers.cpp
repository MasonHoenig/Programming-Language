#include "TacToCpp.h"

#include <unordered_set>
#include <stdexcept>

std::unordered_set<std::string>& declaredNames() {
    static std::unordered_set<std::string> names;
    return names;
}

void resetDeclared() { declaredNames().clear(); }

std::string declOrAssign(const std::string& type, const std::string& name) {
    if (declaredNames().insert(name).second)
        return type + " " + name;
    return name;
}

std::string typeOf(const std::string& s) {
    auto it = types.find(s);
    if (it != types.end()) return it->second;
    if (isBoolean(s)) return "bool";
    if (isInteger(s)) return "int";
    if (isDouble(s))  return "double";
    if (s.size() >= 2 && s.front() == '"') return "std::string";
    throw std::runtime_error("Unknown operand: " + s);
}

std::string textOf(const std::string& s) {
    auto it = names.find(s);
    return it != names.end() ? it->second : s;
}

bool isInteger(const std::string& str) {
	size_t i = (!str.empty() && (str[0] == '-' || str[0] == '+')) ? 1 : 0;
	if (i >= str.size()) return false;
	for (; i < str.size(); ++i)
		if (!std::isdigit(static_cast<unsigned char>(str[i]))) return false;
	return true;
}

bool isDouble(const std::string& str) {
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

bool isBoolean(const std::string& str) {
	return str == "true" || str == "false";
}

std::string escapeForCpp(const std::string& str)
{
	std::string out;
	out.reserve(str.size());
	for (unsigned char c : str)
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

bool isVariableDecl(const std::string& op) {
	return op == "=" || op == "=str";
}

bool isArithmetic(const std::string& op) {
	return op == "+" || op == "-" || op == "*" || op == "/" || op == "%";
}

bool isBooleanEx(const std::string& op) {
	return op == ">" || op == "<" || op == ">=" || op == "<=" || op == "==" || op == "!=" || op == "&&" || op == "&&";
}

void clearResultKeys() {
	for (auto it = names.begin(); it != names.end(); )
		it = (!it->first.empty() && it->first[0] == '#') ? names.erase(it) : std::next(it);
	for (auto it = types.begin(); it != types.end(); )
		it = (!it->first.empty() && it->first[0] == '#') ? types.erase(it) : std::next(it);
}