#include <functional>
#include <memory>
#include <optional>
#include <unordered_map>

#include "ast.hpp"
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
    std::function<std::unique_ptr<Expression>(Parser *, Token)> prefix;
    std::function<std::unique_ptr<Expression>(Parser *, Token, std::unique_ptr<Expression> left)> infix;
    Precedence precedence;

    ParseRule() : prefix(nullptr), infix(nullptr), precedence(NONE) {}
    ParseRule(std::function<std::unique_ptr<Expression>(Parser *, Token)> prefix,
              std::function<std::unique_ptr<Expression>(Parser *, Token, std::unique_ptr<Expression>)> infix,
              Precedence precedence)
        : prefix(prefix), infix(infix), precedence(precedence) {}
};

class Parser {
public:
    Parser(const std::string &source) : scanner(std::make_unique<Scanner>(source)), current(), peek() {
        advance();
        init_rules();
    }

    std::unique_ptr<Statement> parse_statement();

private:
    std::unique_ptr<Scanner> scanner;
    std::optional<Token> current;
    std::optional<Token> peek;

    std::unordered_map<TokenType, ParseRule> rules;

    void init_rules() {
        rules[TokenType::NUMBER] = ParseRule(&Parser::parse_number, nullptr, Precedence::NONE);
        rules[TokenType::LPAREN] = ParseRule(&Parser::parse_grouping, nullptr, Precedence::NONE);
        rules[TokenType::RPAREN] = ParseRule();
        rules[TokenType::COLON] = ParseRule();
        rules[TokenType::SEMICOLON] = ParseRule();
        rules[TokenType::EQUAL] = ParseRule();
        rules[TokenType::PLUS] = ParseRule(nullptr, &Parser::parse_binary, Precedence::TERM);
        rules[TokenType::MINUS] = ParseRule(&Parser::parse_unary, &Parser::parse_binary, Precedence::TERM);
        rules[TokenType::STAR] = ParseRule(nullptr, &Parser::parse_binary, Precedence::FACTOR);
        rules[TokenType::SLASH] = ParseRule(nullptr, &Parser::parse_binary, Precedence::FACTOR);
        rules[TokenType::PRINT] = ParseRule();
        rules[TokenType::END_OF_FILE] = ParseRule();
    }

    std::unique_ptr<Expression> parse_expression(Precedence prec = Precedence::TERM);
    std::unique_ptr<ExpressionStatement> parse_expression_statement();

    std::unique_ptr<Expression> parse_number(Token token);
    std::unique_ptr<Expression> parse_grouping(Token token);
    std::unique_ptr<Expression> parse_binary(Token token, std::unique_ptr<Expression> left);
    std::unique_ptr<Expression> parse_unary(Token token);
    std::unique_ptr<Statement> parse_print();

    void advance();
    void consume(TokenType type, const std::string &message);

    ParseRule &get_rule(TokenType type) { return rules[type]; }
};
