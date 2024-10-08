#pragma once

#include <vector>

#include "tac_instruction.hpp"

class CodeGenerator {
public:
    CodeGenerator(std::vector<TacInstruction> instructions) : instructions(instructions) {};

    std::string generate();

private:
    std::vector<TacInstruction> instructions;

    int stack_size() const;
};
