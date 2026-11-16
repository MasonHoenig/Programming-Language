#pragma once

#include <string>

#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"
#include "../Intermediate Representation/CodeGeneration.h"
#include "../Parser/AST.h"

void RunCompiler(const std::string& inputPath);