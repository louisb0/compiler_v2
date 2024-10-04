#ifndef AST_H
#define AST_H

// TODO: rework - switch into statements and expressions, any use for namespaces?

#include <memory>
#include <string>
#include <utility>

#include "visitors/visitor.hpp"

class Node {
public:
    virtual ~Node() = default;

    virtual void accept(Visitor &visitor) const = 0;
};

class Statement : public Node {};

class Expression : public Node {};

// Statements
class Print : public Statement {
public:
    Print(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *getExpression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visitPrintStatement(*this); }

private:
    std::unique_ptr<Expression> expr;
};

class ExpressionStatement : public Statement {
public:
    ExpressionStatement(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *getExpression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visitExpressionStatement(*this); }

private:
    std::unique_ptr<Expression> expr;
};

//  Expressions
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

// enum class Type {
//     I32,
// };

// class Declaration : public Statement {
// public:
//     Declaration(Token name, std::unique_ptr<Expression> expr, Type type)
//         : name(name), expr(std::move(expr)), type(type) {}
//
//     void print(int indent = 0) const override {
//         printIndent(indent);
//         std::cout << "Declaration: " << name.lexeme << std::endl;
//         expr->print(indent + 1);
//     }
//
// private:
//     Token name;
//     std::unique_ptr<Expression> expr;
//     Type type;
// };

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

#endif
