#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>

#include "ast.hpp"
#include "parser.hpp"

std::unique_ptr<Expression> Parser::parse_expression(Precedence prec) {
    advance();

    ParseRule &prefix_rule = get_rule(this->current->type);
    if (!prefix_rule.prefix) {
        assert(!"No prefix function found");
    }

    std::unique_ptr<Expression> left = prefix_rule.prefix(this, this->current.value());

    while (prec <= get_rule(this->peek->type).precedence) {
        advance();

        ParseRule &infix_rule = get_rule(this->current->type);
        if (!infix_rule.infix) {
            assert(!"No infix function found");
        }

        left = infix_rule.infix(this, this->current.value(), std::move(left));
    }

    return left;
}

std::unique_ptr<Expression> Parser::parse_grouping(Token token) {
    std::unique_ptr<Expression> expr = parse_expression(Precedence::TERM);
    consume(TokenType::RPAREN, "Expected ')' after grouping expression.");

    return std::make_unique<Grouping>(std::move(expr));
}

std::unique_ptr<Expression> Parser::parse_number(Token token) {
    return std::make_unique<Number>(std::stoi(token.lexeme));
}

std::unique_ptr<Expression> Parser::parse_unary(Token token) {
    return std::make_unique<Unary>(token.lexeme, parse_expression(Precedence::UNARY));
}

std::unique_ptr<Expression> Parser::parse_binary(Token token, std::unique_ptr<Expression> left) {
    Precedence precedence = get_rule(token.type).precedence;
    Precedence increased_precedence = static_cast<Precedence>(static_cast<int>(precedence + 1));

    return std::make_unique<Binary>(token.lexeme, std::move(left), parse_expression(increased_precedence));
}

void Parser::advance() {
    current = peek;
    peek = scanner->read_token();
}

void Parser::consume(TokenType type, const std::string &message) {
    if (this->peek && this->peek->type == type) {
        advance();
    } else {
        throw std::runtime_error(message);
    }
}
