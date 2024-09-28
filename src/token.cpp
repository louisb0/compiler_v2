#include <string>
#include <unordered_map>

#include "token.hpp"

const std::unordered_map<TokenType, std::string> Token::token_to_str = {
    {TokenType::LET, "LET"},
    {TokenType::TYPE_I32, "TYPE_I32"},
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::LPAREN, "LPAREN"},
    {TokenType::RPAREN, "RPAREN"},
    {TokenType::COLON, "COLON"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::EQUAL, "EQUAL"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::STAR, "STAR"},
    {TokenType::SLASH, "SLASH"},
    {TokenType::PRINT, "PRINT"},
    {TokenType::END_OF_FILE, "EOF"},
};

const std::unordered_map<std::string, TokenType> Token::lexeme_to_token{
    {"let", TokenType::LET},
    {"i32", TokenType::TYPE_I32},
    {"print", TokenType::PRINT},
};

std::string Token::str() const {
    auto it = token_to_str.find(type);
    std::string type_str = (it != token_to_str.end()) ? it->second : "UNKNOWN";

    return "Token(" + type_str + ", '" + lexeme + "', line " +
           std::to_string(line) + ")";
}
