#pragma once

#include <memory>

#include "../visitors/visitors.hpp"

#include "expressions.hpp"
#include "node.hpp"

class Statement : public Node {};

class Program : public Statement {
public:
    Program(std::vector<std::unique_ptr<Statement>> stmts) : stmts(std::move(stmts)) {}

    const std::vector<std::unique_ptr<Statement>> &statements() const { return stmts; }

    void accept(Visitor &visitor) const override { visitor.visit_program(*this); }

private:
    std::vector<std::unique_ptr<Statement>> stmts;
};

class Print : public Statement {
public:
    Print(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visit_print_statement(*this); }

private:
    std::unique_ptr<Expression> expr;
};

class ExpressionStatement : public Statement {
public:
    ExpressionStatement(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visit_expression_statement(*this); }

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
