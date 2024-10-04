#pragma once

#include <vector>

class TacInstruction;

class Print;
class ExpressionStatement;
class Binary;
class Unary;
class Grouping;
class Number;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visitPrintStatement(const Print &node) = 0;
    virtual void visitExpressionStatement(const ExpressionStatement &node) = 0;
    virtual void visitBinaryExpression(const Binary &node) = 0;
    virtual void visitUnaryExpression(const Unary &node) = 0;
    virtual void visitGroupingExpression(const Grouping &node) = 0;
    virtual void visitNumberExpression(const Number &node) = 0;
};

class SyntaxTreePrinter : public Visitor {
public:
    void visitPrintStatement(const Print &node) override;
    void visitExpressionStatement(const ExpressionStatement &node) override;
    void visitBinaryExpression(const Binary &node) override;
    void visitUnaryExpression(const Unary &node) override;
    void visitGroupingExpression(const Grouping &node) override;
    void visitNumberExpression(const Number &node) override;
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
