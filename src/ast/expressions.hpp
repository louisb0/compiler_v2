#pragma once

#include <memory>
#include <string>

#include "../token.hpp"
#include "../visitors/visitors.hpp"

#include "node.hpp"

class Expression : public Node {};

// TODO: this doesnt evaluate to things
class Assignment : public Expression {
public:
    Assignment(Token token, std::unique_ptr<Expression> expr) : token(token), expr(std::move(expr)) {}

    const Token name() const { return token; }
    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visit_assignment_expression(*this); }

private:
    Token token;
    std::unique_ptr<Expression> expr;
};

class Variable : public Expression {
public:
    Variable(Token token) : token(token) {}

    const Token name() const { return token; }

    void accept(Visitor &visitor) const override { visitor.visit_variable_expression(*this); }

private:
    Token token;
};

class Binary : public Expression {
public:
    Binary(std::string op_symbol, std::unique_ptr<Expression> left_node, std::unique_ptr<Expression> right_node)
        : op_symbol(op_symbol), left_node(std::move(left_node)), right_node(std::move(right_node)) {};

    const std::string &symbol() const { return op_symbol; }
    const Expression *left() const { return left_node.get(); }
    const Expression *right() const { return right_node.get(); }

    void accept(Visitor &visitor) const override { visitor.visit_binary_expression(*this); }

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

    void accept(Visitor &visitor) const override { visitor.visit_unary_expression(*this); }

private:
    std::string op_symbol;
    std::unique_ptr<Expression> expr;
};

class Grouping : public Expression {
public:
    Grouping(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visit_grouping_expression(*this); }

private:
    std::unique_ptr<Expression> expr;
};

class Number : public Expression {
public:
    Number(int number) : number(number) {}

    int value() const { return number; }

    void accept(Visitor &visitor) const override { visitor.visit_number_expression(*this); }

private:
    int number;
};
