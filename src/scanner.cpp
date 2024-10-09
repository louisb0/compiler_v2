#include <cassert>
#include <cctype>
#include <string>

#include "scanner.hpp"
#include "token.hpp"

Token Scanner::read_token() {
    skip_whitespace();

    this->start = this->current;

    if (is_eof()) {
        return Token(TokenType::END_OF_FILE, "\0", this->line);
    }

    char c = advance();

    if (isdigit(c))
        return number();

    if (isalpha(c))
        return identifier();

    switch (c) {
    case '(':
        return Token(TokenType::LPAREN, "(", this->line);
    case ')':
        return Token(TokenType::RPAREN, ")", this->line);
    case '{':
        return Token(TokenType::LBRACE, "{", this->line);
    case '}':
        return Token(TokenType::RBRACE, "}", this->line);
    case ':':
        return Token(TokenType::COLON, ":", this->line);
    case ';':
        return Token(TokenType::SEMICOLON, ";", this->line);
    case '=':
        return Token(TokenType::EQUAL, "=", this->line);
    case '+':
        return Token(TokenType::PLUS, "+", this->line);
    case '-':
        return Token(TokenType::MINUS, "-", this->line);
    case '*':
        return Token(TokenType::STAR, "*", this->line);
    case '/':
        return Token(TokenType::SLASH, "/", this->line);

    default:
        assert(!"Unrecognized character.");
    }
}

Token Scanner::number() {
    while (isdigit(peek())) {
        advance();
    }

    std::string lexeme = this->source.substr(this->start, this->current - this->start);

    return Token(TokenType::NUMBER, lexeme, this->line);
}

Token Scanner::identifier() {
    while (isalpha(peek()) || isdigit(peek())) {
        advance();
    }

    std::string lexeme = this->source.substr(this->start, this->current - this->start);

    if (TokenUtils::is_keyword(lexeme)) {
        return Token(TokenUtils::lexeme_to_token.at(lexeme), lexeme, this->line);
    }

    return Token(TokenType::IDENTIFIER, lexeme, this->line);
}

void Scanner::skip_whitespace() {
    while (true) {
        char c = peek();
        switch (c) {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;

        case '\n':
            this->line++;
            advance();
            break;

        default:
            return;
        }
    }
}

char Scanner::advance() { return this->source[this->current++]; }

char Scanner::peek() const { return this->source[this->current]; }

bool Scanner::is_eof() const { return this->current == this->source.length(); }
