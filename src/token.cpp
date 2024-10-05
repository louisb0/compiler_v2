#include <string>
#include <unordered_map>

#include "token.hpp"

// TODO: reconsider this when you wake up
namespace TokenUtils {
    const std::unordered_map<TokenType, std::string> token_to_string = {
        {TokenType::LET, "LET"},       {TokenType::TYPE_I32, "TYPE_I32"},   {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::NUMBER, "NUMBER"}, {TokenType::LPAREN, "LPAREN"},       {TokenType::RPAREN, "RPAREN"},
        {TokenType::COLON, "COLON"},   {TokenType::SEMICOLON, "SEMICOLON"}, {TokenType::EQUAL, "EQUAL"},
        {TokenType::PLUS, "PLUS"},     {TokenType::MINUS, "MINUS"},         {TokenType::STAR, "STAR"},
        {TokenType::SLASH, "SLASH"},   {TokenType::PRINT, "PRINT"},         {TokenType::END_OF_FILE, "EOF"},
    };

    const std::unordered_map<std::string, TokenType> lexeme_to_token = {
        {"let", TokenType::LET},
        {"i32", TokenType::TYPE_I32},
        {"print", TokenType::PRINT},
    };

    bool is_keyword(const std::string &lexeme) { return lexeme_to_token.find(lexeme) != lexeme_to_token.end(); }

    std::string token_type_to_string(TokenType type) {
        auto it = token_to_string.find(type);
        return (it != token_to_string.end()) ? it->second : "UNKNOWN";
    }
} // namespace TokenUtils

std::string Token::to_string() const {
    std::string type_string = TokenUtils::token_type_to_string(type);
    return "Token(" + type_string + ", '" + lexeme + "', line " + std::to_string(line) + ")";
}
