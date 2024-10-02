#include "tac_generator.hpp"

void TacGenerator::visitPrintStatement(const Print &node) {
    node.getExpression()->accept(*this);

    this->instructions.push_back(TacInstruction(TacOperation::PRINT, this->instructions.size() - 1));
};

void TacGenerator::visitExpressionStatement(const ExpressionStatement &node) { node.getExpression()->accept(*this); };

void TacGenerator::visitBinaryExpression(const Binary &node) {
    node.getLeft()->accept(*this);
    int leftIndex = this->instructions.size() - 1;

    node.getRight()->accept(*this);
    int rightIndex = this->instructions.size() - 1;

    TacOperation op;
    switch (node.getOperator()[0]) {
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
    node.getExpression()->accept(*this);

    this->instructions.push_back(TacInstruction(TacOperation::NEG, this->instructions.size() - 1));
}

void TacGenerator::visitGroupingExpression(const Grouping &node) { node.getExpression()->accept(*this); };

void TacGenerator::visitNumberExpression(const Number &node) {
    this->instructions.push_back(TacInstruction(TacOperation::VALUE, node.getValue()));
}
