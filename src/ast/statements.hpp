#pragma once

#include <memory>

#include "../visitors/visitor.hpp"
#include "expressions.hpp"
#include "node.hpp"

class Statement : public Node {};

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
