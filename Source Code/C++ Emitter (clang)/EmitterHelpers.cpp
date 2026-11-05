#include "TacToCpp.h"

#include <string>
#include <type_traits>
#include <variant>
#include <charconv>
#include <sstream>

namespace tac_helpers {

    std::string WriteCpp(const Instr& instr) {
        std::ostringstream output;
        std::string errorMessage;
        if (emitArithmetic(instr, output, errorMessage)) {
            return output.str();
        }
        return "Error: " + errorMessage + "\n";
    }

    std::string escape(const std::string& s) {
        std::string r;
        for (char c : s) {
            switch (c) {
            case '\\': r += "\\\\"; break;
            case '"':  r += "\\\""; break;
            case '\n': r += "\\n";  break;
            case '\t': r += "\\t";  break;
            default:   r += c;
            }
        }
        return r;
    }

    std::string doubleLiteral(double value) {
        char buffer[64];
        auto res = std::to_chars(buffer, buffer + sizeof(buffer), value);
        std::string x(buffer, res.ptr);
        return x;
    }

    inline std::string convertOperandValue(std::monostate) { return "{}"; }
    inline std::string convertOperandValue(const Var& x) { return x.name; }
    inline std::string convertOperandValue(int x) { return std::to_string(x); }
    inline std::string convertOperandValue(double x) { return doubleLiteral(x); }
    inline std::string convertOperandValue(bool x) { return x ? "true" : "false"; }
    inline std::string convertOperandValue(const StrLit& x) { return "\"" + escape(x.value) + "\""; }

    std::string operandToCpp(const Operand& operand) {
        return std::visit([](const auto& x) -> std::string {
            return convertOperandValue(x);
        }, operand);
    }

    const char* cppType(Type type) {
        switch (type) {
        case Type::Number: return "int";
        case Type::Text: return "std::string";
        case Type::Boolean: return "bool";
        }
        return "int";
    }

    bool hasValue(const Operand& operand) {
        return !std::holds_alternative<std::monostate>(operand);
    }
}