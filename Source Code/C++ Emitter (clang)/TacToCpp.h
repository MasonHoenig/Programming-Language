#pragma once
#include "../Intermediate Representation/TAC.h"

#include <optional>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

enum class Type { Int, Double, Bool, String };

struct Symbol
{
    std::string cppName;
    Type type;
};

struct VariableDeclaration
{
    int nextId = 0;
    std::unordered_map<std::string, std::string> names;
    std::unordered_map<std::string, std::string> types;

    std::string variableDeclaration(const TAC& tac);
};

std::vector<std::string> emitCpp(const std::vector<std::vector<TAC>>& ir);