#ifndef VISITOR_H
#define VISITOR_H

//
// vector/array of instructions
// we just store the index into the instruction
//
// e.g. add t1, t2 => we can use 1/2 as indexes into the vector to get the other instructions
//
// operation
// operand1 (int)
// operand2 (int)
//

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

#endif
