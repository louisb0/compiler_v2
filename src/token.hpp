#pragma once

#include <string>
#include <unordered_map>

enum TokenType {
    LET,
    TYPE_I32,
    IDENTIFIER,
    NUMBER,

    LPAREN,
    RPAREN,

    COLON,
    SEMICOLON,
    EQUAL,

    PLUS,
    MINUS,
    STAR,
    SLASH,

    PRINT,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    // is it bad having these attached to a struct?
    static const std::unordered_map<TokenType, std::string> token_to_str;
    static const std::unordered_map<std::string, TokenType> lexeme_to_token;

    Token(TokenType type, const std::string &lexeme, int line) : type(type), lexeme(lexeme), line(line) {}

    std::string str() const;
};
