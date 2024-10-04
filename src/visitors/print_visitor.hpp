#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

#include "visitor.hpp"

class PrintVisitor : public Visitor {
public:
    void visitPrintStatement(const Print &node) override;
    void visitExpressionStatement(const ExpressionStatement &node) override;
    void visitBinaryExpression(const Binary &node) override;
    void visitUnaryExpression(const Unary &node) override;
    void visitGroupingExpression(const Grouping &node) override;
    void visitNumberExpression(const Number &node) override;
};

#endif
