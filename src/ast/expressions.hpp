#pragma once

#include <memory>
#include <string>

#include "../visitors/visitor.hpp"
#include "node.hpp"

class Visitor;

class Expression : public Node {};

class Binary : public Expression {
public:
    Binary(std::string op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : op(op), left(std::move(left)), right(std::move(right)) {};

    const std::string &getOperator() const { return op; }
    const Expression *getLeft() const { return left.get(); }
    const Expression *getRight() const { return right.get(); }

    void accept(Visitor &visitor) const override { visitor.visitBinaryExpression(*this); }

private:
    std::string op;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

class Unary : public Expression {
public:
    Unary(std::string op, std::unique_ptr<Expression> expr) : op(op), expr(std::move(expr)) {}

    const std::string &getOperator() const { return op; }
    const Expression *getExpression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visitUnaryExpression(*this); }

private:
    std::string op;
    std::unique_ptr<Expression> expr;
};

class Grouping : public Expression {
public:
    Grouping(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *getExpression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visitGroupingExpression(*this); }

private:
    std::unique_ptr<Expression> expr;
};

class Number : public Expression {
public:
    Number(int value) : value(value) {}

    const int getValue() const { return value; }

    void accept(Visitor &visitor) const override { visitor.visitNumberExpression(*this); }

private:
    int value;
};

// class Assignment : public Expression {
// public:
//     Assignment(Token name, std::unique_ptr<Expression> expr) : name(name), expr(std::move(expr)) {}
//
//     void print(int indent = 0) const override {
//         printIndent(indent);
//         std::cout << "Assignment: " << name.lexeme << std::endl;
//         expr->print(indent + 1);
//     }
//
// private:
//     Token name;
//     std::unique_ptr<Expression> expr;
// };

// class Variable : public Expression {
// public:
//     Variable(Token name) : name(name) {}
//
//     void print(int indent = 0) const override {
//         printIndent(indent);
//         std::cout << "Variable: " << name.lexeme << std::endl;
//     }
//
// private:
//     Token name;
// };
