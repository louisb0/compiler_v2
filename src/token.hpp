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
    LBRACE,
    RBRACE,

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

    Token(TokenType type, const std::string &lexeme, int line) : type(type), lexeme(lexeme), line(line) {}

    std::string to_string() const;
};

namespace TokenUtils {
    extern const std::unordered_map<TokenType, std::string> token_to_string;
    extern const std::unordered_map<std::string, TokenType> lexeme_to_token;

    bool is_keyword(const std::string &lexeme);
    std::string token_type_to_string(TokenType type);
} // namespace TokenUtils
