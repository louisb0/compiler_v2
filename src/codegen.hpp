#include <vector>

#include "visitors/tac_generator.hpp"

class CodeGenerator {
public:
    CodeGenerator(std::vector<TacInstruction> instructions) : instructions(instructions) {};

    std::string generate();

private:
    std::vector<TacInstruction> instructions;

    int calc_stack_size();
};
