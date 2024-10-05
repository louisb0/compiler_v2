#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <unordered_map>

#include "ast/expressions.hpp"
#include "ast/statements.hpp"

#include "scanner.hpp"
#include "token.hpp"

enum Precedence {
    NONE,
    TERM,
    FACTOR,
    UNARY,
};

class Parser;

struct ParseRule {
    std::function<std::unique_ptr<Expression>(Parser *, const Token)> prefix;
    std::function<std::unique_ptr<Expression>(Parser *, const Token, std::unique_ptr<Expression> left)> infix;
    const Precedence precedence;

    ParseRule() : prefix(nullptr), infix(nullptr), precedence(NONE) {}
    ParseRule(std::function<std::unique_ptr<Expression>(Parser *, const Token)> prefix,
              std::function<std::unique_ptr<Expression>(Parser *, const Token, std::unique_ptr<Expression>)> infix,
              const Precedence precedence)
        : prefix(prefix), infix(infix), precedence(precedence) {}
};

class Parser {
public:
    Parser(const std::string &source) : scanner(std::make_unique<Scanner>(source)), current(), peek() {
        advance();
        init_rules();
    }

    std::unique_ptr<Program> parse();

private:
    std::unique_ptr<Scanner> scanner;
    std::optional<Token> current;
    std::optional<Token> peek;

    std::unordered_map<TokenType, ParseRule> rules;

    void init_rules() {
        rules.emplace(TokenType::NUMBER, ParseRule(&Parser::number, nullptr, Precedence::NONE));
        rules.emplace(TokenType::LPAREN, ParseRule(&Parser::grouping, nullptr, Precedence::NONE));
        rules.emplace(TokenType::RPAREN, ParseRule());
        rules.emplace(TokenType::COLON, ParseRule());
        rules.emplace(TokenType::SEMICOLON, ParseRule());
        rules.emplace(TokenType::EQUAL, ParseRule());
        rules.emplace(TokenType::PLUS, ParseRule(nullptr, &Parser::binary, Precedence::TERM));
        rules.emplace(TokenType::MINUS, ParseRule(&Parser::unary, &Parser::binary, Precedence::TERM));
        rules.emplace(TokenType::STAR, ParseRule(nullptr, &Parser::binary, Precedence::FACTOR));
        rules.emplace(TokenType::SLASH, ParseRule(nullptr, &Parser::binary, Precedence::FACTOR));
        rules.emplace(TokenType::PRINT, ParseRule());
        rules.emplace(TokenType::IDENTIFIER, ParseRule(&Parser::variable, nullptr, Precedence::NONE));
        rules.emplace(TokenType::END_OF_FILE, ParseRule());
    }

    std::unique_ptr<Statement> declaration();
    std::unique_ptr<Statement> statement();
    std::unique_ptr<ExpressionStatement> expression_statement();

    // where?
    std::unique_ptr<Declaration> var_declaration();

    std::unique_ptr<Expression> expression(const Precedence prec = Precedence::TERM);
    std::unique_ptr<Expression> number(const Token token);
    std::unique_ptr<Expression> grouping(const Token token);
    std::unique_ptr<Expression> binary(const Token token, std::unique_ptr<Expression> left);
    std::unique_ptr<Expression> unary(const Token token);
    std::unique_ptr<Expression> variable(const Token token);
    std::unique_ptr<Statement> print();

    void advance();
    void consume(const TokenType type, const std::string &message);

    const ParseRule &rule_for(TokenType type) const { return rules.at(type); }
};
