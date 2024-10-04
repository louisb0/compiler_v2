#include <iostream>

#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"

#include "print_visitor.hpp"

void PrintVisitor::visitPrintStatement(const Print &node) {
    std::cout << "print(";
    node.getExpression()->accept(*this);
    std::cout << ");" << std::endl;
}

void PrintVisitor::visitExpressionStatement(const ExpressionStatement &node) { node.getExpression()->accept(*this); }

void PrintVisitor::visitBinaryExpression(const Binary &node) {
    node.getLeft()->accept(*this);
    std::cout << " " << node.getOperator() << " ";
    node.getRight()->accept(*this);
}

void PrintVisitor::visitUnaryExpression(const Unary &node) {
    std::cout << node.getOperator();
    node.getExpression()->accept(*this);
}

void PrintVisitor::visitGroupingExpression(const Grouping &node) {
    std::cout << "(";
    node.getExpression()->accept(*this);
    std::cout << ")";
}

void PrintVisitor::visitNumberExpression(const Number &node) { std::cout << node.getValue(); }
