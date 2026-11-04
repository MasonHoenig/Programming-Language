#include "TacToCpp.h"

#include <sstream>
#include <type_traits>

using namespace tac_helpers;

bool tac_helpers::emitDeclaration(const Instr& instr, std::ostream& output, std::string errorMessage) {

    if (instr.operand != Operator::Decl) {
		errorMessage = "Instruction is not a declaration";
		return false;
    }
    if (instr.dest.empty()) {
        errorMessage = "Declaration has no destination";
        return false;
    }

	output << "    " << cppType(instr.type) << ' ' << instr.dest;

    if (hasValue(instr.a) || std::holds_alternative<StrLit>(instr.a))
        output << " = " << operandToCpp(instr.a) << ";\n";
    else
        output << "{};\n";

    return true;
}