#pragma once

#include <memory>
#include <string>

#include "../visitors/visitors.hpp"
#include "node.hpp"

class Visitor;

class Expression : public Node {};

class Binary : public Expression {
public:
    Binary(std::string op_symbol, std::unique_ptr<Expression> left_node, std::unique_ptr<Expression> right_node)
        : op_symbol(op_symbol), left_node(std::move(left_node)), right_node(std::move(right_node)) {};

    const std::string &symbol() const { return op_symbol; }
    const Expression *left() const { return left_node.get(); }
    const Expression *right() const { return right_node.get(); }

    void accept(Visitor &visitor) const override { visitor.visitBinaryExpression(*this); }

private:
    std::string op_symbol;
    std::unique_ptr<Expression> left_node;
    std::unique_ptr<Expression> right_node;
};

class Unary : public Expression {
public:
    Unary(std::string op_symbol, std::unique_ptr<Expression> expr) : op_symbol(op_symbol), expr(std::move(expr)) {}

    const std::string &symbol() const { return op_symbol; }
    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visitUnaryExpression(*this); }

private:
    std::string op_symbol;
    std::unique_ptr<Expression> expr;
};

class Grouping : public Expression {
public:
    Grouping(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visitGroupingExpression(*this); }

private:
    std::unique_ptr<Expression> expr;
};

class Number : public Expression {
public:
    Number(int number) : number(number) {}

    int value() const { return number; }

    void accept(Visitor &visitor) const override { visitor.visitNumberExpression(*this); }

private:
    int number;
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
