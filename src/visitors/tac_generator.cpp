#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"
#include "../tac_instruction.hpp"

#include "visitors.hpp"

void TacGenerator::visitPrintStatement(const Print &node) {
    node.expression()->accept(*this);

    this->instructions.push_back(TacInstruction(TacOperation::PRINT, this->instructions.size() - 1));
};

void TacGenerator::visitExpressionStatement(const ExpressionStatement &node) { node.expression()->accept(*this); };

void TacGenerator::visitBinaryExpression(const Binary &node) {
    node.left()->accept(*this);
    int leftIndex = this->instructions.size() - 1;

    node.right()->accept(*this);
    int rightIndex = this->instructions.size() - 1;

    TacOperation op;
    switch (node.symbol()[0]) {
    case '+':
        op = TacOperation::ADD;
        break;
    case '-':
        op = TacOperation::SUB;
        break;
    case '*':
        op = TacOperation::MUL;
        break;
    case '/':
        op = TacOperation::DIV;
        break;
    }

    this->instructions.push_back(TacInstruction(op, leftIndex, rightIndex));
};

void TacGenerator::visitUnaryExpression(const Unary &node) {
    node.expression()->accept(*this);

    this->instructions.push_back(TacInstruction(TacOperation::NEG, this->instructions.size() - 1));
}

void TacGenerator::visitGroupingExpression(const Grouping &node) { node.expression()->accept(*this); };

void TacGenerator::visitNumberExpression(const Number &node) {
    this->instructions.push_back(TacInstruction(TacOperation::VALUE, node.value()));
}
