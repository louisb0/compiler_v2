#ifndef TAC_GENERATOR_H
#define TAC_GENERATOR_H

#include <string>
#include <vector>

#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"

#include "visitor.hpp"

enum class TacOperation {
    VALUE,
    NEG,
    ADD,
    SUB,
    MUL,
    DIV,
    PRINT,
};

struct TacInstruction {
    TacInstruction(TacOperation op, int operand1, int operand2 = -1) : op(op), operand1(operand1), operand2(operand2) {}

    TacOperation op;
    int operand1;
    int operand2;

    std::string str(int tac_index) const {
        std::string result = "t" + std::to_string(tac_index) + " <- ";

        switch (op) {
        case TacOperation::VALUE:
            result += std::to_string(operand1);
            break;
        case TacOperation::NEG:
            result += "neg t" + std::to_string(operand1);
            break;
        case TacOperation::ADD:
            result += "add t" + std::to_string(operand1) + ", t" + std::to_string(operand2);
            break;
        case TacOperation::SUB:
            result += "sub t" + std::to_string(operand1) + ", t" + std::to_string(operand2);
            break;
        case TacOperation::MUL:
            result += "mul t" + std::to_string(operand1) + ", t" + std::to_string(operand2);
            break;
        case TacOperation::DIV:
            result += "div t" + std::to_string(operand1) + ", t" + std::to_string(operand2);
            break;
        case TacOperation::PRINT:
            result = "print(t" + std::to_string(operand1) + ")";
            break;
        }

        return result;
    }
};

class TacGenerator : public Visitor {
public:
    std::vector<TacInstruction> instructions;

    void visitPrintStatement(const Print &node) override;
    void visitExpressionStatement(const ExpressionStatement &node) override;
    void visitBinaryExpression(const Binary &node) override;
    void visitUnaryExpression(const Unary &node) override;
    void visitGroupingExpression(const Grouping &node) override;
    void visitNumberExpression(const Number &node) override;
};

#endif
