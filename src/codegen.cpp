#include "codegen.hpp"
#include "visitors/tac_generator.hpp"

const std::string header = R"(
.data
    integer_format: .string "%d\n"

.text
    .globl main

main:
    /* prologue */
    pushl %ebp
    movl %esp, %ebp

)";

const std::string footer = R"(    /* epilogue */
    movl $0, %eax
    movl %ebp, %esp
    pop %ebp
    ret
)";

std::string CodeGenerator::generate() {
    int stack_size = calc_stack_size();

    std::string generated_code = "    sub $" + std::to_string(stack_size) + ", %esp\n\n";

    for (int i = 0; i < this->instructions.size(); i++) {
        TacInstruction inst = this->instructions.at(i);

        int result_index = i * 4;

        switch (inst.op) {
        case TacOperation::VALUE:
            // clang-format off
            generated_code += "    movl $" + std::to_string(inst.operand1) + ", %eax\n"
                              "    movl %eax, -" + std::to_string(result_index) + "(%ebp)\n\n";
            // clang-format on
            break;

        case TacOperation::NEG:
            // clang-format off
            generated_code += "    movl -" + std::to_string(4 * inst.operand1) + "(%ebp), %eax\n"
                              "    neg %eax\n"
                              "    movl %eax, -" + std::to_string(result_index) + "(%ebp)\n\n";
            // clang-format on
            break;

        case TacOperation::ADD:
            // clang-format off
            generated_code += "    movl -" + std::to_string(4 * inst.operand1) + "(%ebp), %eax\n"
                              "    addl -" + std::to_string(4 * inst.operand2) + "(%ebp), %eax\n"
                              "    movl %eax, -" + std::to_string(result_index) + "(%ebp)\n\n";
            // clang-format on
            break;

        case TacOperation::SUB:
            // clang-format off
            generated_code += "    movl -" + std::to_string(4 * inst.operand1) + "(%ebp), %eax\n"
                              "    subl -" + std::to_string(4 * inst.operand2) + "(%ebp), %eax\n"
                              "    movl %eax, -" + std::to_string(result_index) + "(%ebp)\n\n";
            // clang-format on
            break;

        case TacOperation::MUL:
            // clang-format off
            generated_code += "    movl -" + std::to_string(4 * inst.operand1) + "(%ebp), %eax\n"
                              "    mull -" + std::to_string(4 * inst.operand2) + "(%ebp)\n"
                              "    movl %eax, -" + std::to_string(result_index) + "(%ebp)\n\n";
            // clang-format on
            break;

        case TacOperation::DIV:
            // clang-format off
            generated_code += "    movl -" + std::to_string(4 * inst.operand1) + "(%ebp), %eax\n"
                              "    cdq\n"
                              "    idivl -" + std::to_string(4 * inst.operand2) + "(%ebp)\n"
                              "    movl %eax, -" + std::to_string(result_index) + "(%ebp)\n\n";
            // clang-format on
            break;

        case TacOperation::PRINT:
            // clang-format off
            generated_code += "    pushl -" + std::to_string(4 * inst.operand1) + "(%ebp)\n"
                              "    pushl $integer_format\n"
                              "    call printf\n"
                              "    addl $8, %esp\n\n";
            // clang-format on
            break;
        }
    }

    return header + generated_code + footer;
}

int CodeGenerator::calc_stack_size() {
    int stack_size = 0;
    for (TacInstruction t : this->instructions) {
        if (t.op != TacOperation::PRINT)
            stack_size += 4;
    }

    return stack_size;
}
