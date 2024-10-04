#include <iostream>

#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"

#include "visitors.hpp"

void SyntaxTreePrinter::visitPrintStatement(const Print &node) {
    std::cout << "print(";
    node.expression()->accept(*this);
    std::cout << ");" << std::endl;
}

void SyntaxTreePrinter::visitExpressionStatement(const ExpressionStatement &node) { node.expression()->accept(*this); }

void SyntaxTreePrinter::visitBinaryExpression(const Binary &node) {
    node.left()->accept(*this);
    std::cout << " " << node.symbol() << " ";
    node.right()->accept(*this);
}

void SyntaxTreePrinter::visitUnaryExpression(const Unary &node) {
    std::cout << node.symbol();
    node.expression()->accept(*this);
}

void SyntaxTreePrinter::visitGroupingExpression(const Grouping &node) {
    std::cout << "(";
    node.expression()->accept(*this);
    std::cout << ")";
}

void SyntaxTreePrinter::visitNumberExpression(const Number &node) { std::cout << node.value(); }
