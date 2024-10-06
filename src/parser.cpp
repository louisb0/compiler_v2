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
    if (this->peek->type == TokenType::LET) {
        return var_declaration();
    } else {
        return statement();
    }
}

std::unique_ptr<Declaration> Parser::var_declaration() {
    advance();

    consume(TokenType::IDENTIFIER, "Expected variable name after 'let'.");
    Token identifier = this->current.value();

    consume(TokenType::COLON, "Expected type definition as part of variable declaration.");

    // TODO: add type to string, token to type
    consume(TokenType::TYPE_I32, "Expected type definition as part of variable declaration.");
    Type type = Type::I32;

    consume(TokenType::EQUAL, "Expected '=' as part of variable declaration.");

    std::unique_ptr<Expression> expr = expression();
    consume(TokenType::SEMICOLON, "Expected ';' after variable declaration.");

    return std::make_unique<Declaration>(identifier, type, std::move(expr));
}

std::unique_ptr<Statement> Parser::statement() {
    if (this->peek->type == TokenType::PRINT) {
        return print();
    } else {
        return expression_statement();
    }
}

std::unique_ptr<Statement> Parser::print() {
    advance();
    consume(TokenType::LPAREN, "Expected '(' after print.");

    std::unique_ptr<Expression> expr = expression();

    consume(TokenType::RPAREN, "Expected ')' after call to print.");
    consume(TokenType::SEMICOLON, "Expected ';' after call to print.");

    return std::make_unique<Print>(std::move(expr));
}

std::unique_ptr<ExpressionStatement> Parser::expression_statement() {
    std::unique_ptr<Expression> expr = expression();
    consume(TokenType::SEMICOLON, "Expected ';' after expression.");

    return std::make_unique<ExpressionStatement>(std::move(expr));
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

std::unique_ptr<Expression> Parser::grouping(const Token token) {
    std::unique_ptr<Expression> expr = expression(Precedence::TERM);
    consume(TokenType::RPAREN, "Expected ')' after grouping expression.");

    return std::make_unique<Grouping>(std::move(expr));
}

std::unique_ptr<Expression> Parser::number(const Token token) {
    return std::make_unique<Number>(std::stoi(token.lexeme));
}

std::unique_ptr<Expression> Parser::unary(const Token token) {
    return std::make_unique<Unary>(token.lexeme, expression(Precedence::UNARY));
}

std::unique_ptr<Expression> Parser::binary(const Token token, std::unique_ptr<Expression> left) {
    Precedence precedence = rule_for(token.type).precedence;
    Precedence increased_precedence = static_cast<Precedence>(static_cast<int>(precedence + 1));

    return std::make_unique<Binary>(token.lexeme, std::move(left), expression(increased_precedence));
}

std::unique_ptr<Expression> Parser::variable(const Token token) {
    if (this->peek->type == TokenType::EQUAL) {
        advance();
        std::unique_ptr<Expression> expr = expression();

        return std::make_unique<Assignment>(token, std::move(expr));
    } else {
        return std::make_unique<Variable>(token);
    }
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
