#include <iostream>

#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"

#include "visitors.hpp"

void SyntaxTreePrinter::visitPrintStatement(const Print &node) {
    std::cout << "print(";
    node.getExpression()->accept(*this);
    std::cout << ");" << std::endl;
}

void SyntaxTreePrinter::visitExpressionStatement(const ExpressionStatement &node) {
    node.getExpression()->accept(*this);
}

void SyntaxTreePrinter::visitBinaryExpression(const Binary &node) {
    node.getLeft()->accept(*this);
    std::cout << " " << node.getOperator() << " ";
    node.getRight()->accept(*this);
}

void SyntaxTreePrinter::visitUnaryExpression(const Unary &node) {
    std::cout << node.getOperator();
    node.getExpression()->accept(*this);
}

void SyntaxTreePrinter::visitGroupingExpression(const Grouping &node) {
    std::cout << "(";
    node.getExpression()->accept(*this);
    std::cout << ")";
}

void SyntaxTreePrinter::visitNumberExpression(const Number &node) { std::cout << node.getValue(); }
