#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "ast/expressions.hpp"
#include "ast/statements.hpp"

#include "parser.hpp"
#include "token.hpp"

std::unique_ptr<Program> Parser::parse() {
    std::vector<std::unique_ptr<Statement>> stmts;

    while (this->peek->type != TokenType::END_OF_FILE) {
        stmts.push_back(std::move(declaration()));
    }

    return std::make_unique<Program>(std::move(stmts));
}

std::unique_ptr<Statement> Parser::declaration() {
    std::unique_ptr<Statement> stmt;
    if (match(TokenType::LET)) {
        stmt = var_declaration();
    } else {
        stmt = statement();
    }

    consume(TokenType::SEMICOLON, "Expected ';' after statement or declaration.");
    return stmt;
}

std::unique_ptr<Declaration> Parser::var_declaration() {
    consume(TokenType::IDENTIFIER, "Expected variable name after 'let'.");
    Token identifier = this->current.value();

    consume(TokenType::COLON, "Expected type definition as part of variable declaration.");
    Type type = parse_type();

    consume(TokenType::EQUAL, "Expected '=' as part of variable declaration.");

    std::unique_ptr<Expression> expr = expression();

    return std::make_unique<Declaration>(identifier, type, std::move(expr));
}

std::unique_ptr<Statement> Parser::statement() {
    if (match(TokenType::PRINT)) {
        return print();
    } else {
        return expression_statement();
    }
}

std::unique_ptr<Statement> Parser::print() {
    consume(TokenType::LPAREN, "Expected '(' as part of call to print.");
    std::unique_ptr<Expression> expr = expression();
    consume(TokenType::RPAREN, "Expected ')' as part of call to print.");

    return std::make_unique<Print>(std::move(expr));
}

std::unique_ptr<ExpressionStatement> Parser::expression_statement() {
    return std::make_unique<ExpressionStatement>(std::move(expression()));
}

std::unique_ptr<Expression> Parser::expression(const Precedence prec) {
    advance();

    const ParseRule &prefix_rule = rule_for(this->current->type);
    if (!prefix_rule.prefix) {
        std::runtime_error("No prefix function found");
    }

    std::unique_ptr<Expression> left = prefix_rule.prefix(this, this->current.value());

    while (prec <= rule_for(this->peek->type).precedence) {
        advance();

        const ParseRule &infix_rule = rule_for(this->current->type);
        if (!infix_rule.infix) {
            std::runtime_error("No infix function found");
        }

        left = infix_rule.infix(this, this->current.value(), std::move(left));
    }

    return left;
}

std::unique_ptr<Expression> Parser::variable(const Token token) {
    if (match(TokenType::EQUAL)) {
        return std::make_unique<Assignment>(token, std::move(expression()));
    } else {
        return std::make_unique<Variable>(token);
    }
}

std::unique_ptr<Expression> Parser::binary(const Token token, std::unique_ptr<Expression> left) {
    auto right = expression(rule_for(token.type).next_precedence());

    return std::make_unique<Binary>(token, std::move(left), std::move(right));
}

std::unique_ptr<Expression> Parser::unary(const Token token) {
    return std::make_unique<Unary>(token, expression(Precedence::UNARY));
}

std::unique_ptr<Expression> Parser::grouping(const Token token) {
    auto expr = expression(Precedence::TERM);
    consume(TokenType::RPAREN, "Expected ')' after grouping expression.");

    return std::make_unique<Grouping>(std::move(expr));
}

std::unique_ptr<Expression> Parser::number(const Token token) {
    return std::make_unique<Number>(std::stoi(token.lexeme));
}

void Parser::advance() {
    current = peek;
    peek = scanner->read_token();
}

void Parser::consume(const TokenType type, const std::string &message) {
    if (this->peek && this->peek->type == type) {
        advance();
    } else {
        throw std::runtime_error(message);
    }
}

bool Parser::match(const TokenType type) {
    if (this->peek && this->peek->type == type) {
        advance();
        return true;
    }

    return false;
}

Type Parser::parse_type() {
    if (match(TokenType::TYPE_I32)) {
        return Type::I32;
    } else {
        throw std::runtime_error("Expected a valid type.");
    }
}
