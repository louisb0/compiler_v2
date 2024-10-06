#pragma once

#include <memory>

#include "../token.hpp"
#include "../visitors/visitors.hpp"

#include "expressions.hpp"
#include "node.hpp"

enum class Type {
    I32,
};

class Statement : public Node {};

class Program : public Statement {
public:
    Program(std::vector<std::unique_ptr<Statement>> stmts) : stmts(std::move(stmts)) {}

    const std::vector<std::unique_ptr<Statement>> &statements() const { return stmts; }

    void accept(Visitor &visitor) const override { visitor.visit_program(*this); }

private:
    std::vector<std::unique_ptr<Statement>> stmts;
};

class ExpressionStatement : public Statement {
public:
    ExpressionStatement(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visit_expression_statement(*this); }

private:
    std::unique_ptr<Expression> expr;
};

class Declaration : public Statement {
public:
    Declaration(Token token, Type type, std::unique_ptr<Expression> expr)
        : token(token), expr(std::move(expr)), type(type) {}

    const Token name() const { return token; }
    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visit_declaration_statement(*this); }

private:
    Token token;
    std::unique_ptr<Expression> expr;
    Type type;
};

class Print : public Statement {
public:
    Print(std::unique_ptr<Expression> expr) : expr(std::move(expr)) {}

    const Expression *expression() const { return expr.get(); }

    void accept(Visitor &visitor) const override { visitor.visit_print_statement(*this); }

private:
    std::unique_ptr<Expression> expr;
};
