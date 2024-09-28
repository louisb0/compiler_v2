#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "scanner.hpp"
#include "token.hpp"

std::vector<Token> Scanner::read_tokens() {
    std::vector<Token> tokens;
    while (!is_eof()) {
        Token token = read_token();
        std::cout << token.str() << std::endl;
        tokens.push_back(token);
    }

    return tokens;
}

Token Scanner::read_token() {
    skip_whitespace();

    this->start = this->current;

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

    std::string lexeme =
        this->source.substr(this->start, this->current - this->start);

    return Token(TokenType::NUMBER, lexeme, this->line);
}

Token Scanner::identifier() {
    while (isalpha(peek())) {
        advance();
    }

    std::string lexeme =
        this->source.substr(this->start, this->current - this->start);

    auto it = Token::lexeme_to_token.find(lexeme);
    if (it != Token::lexeme_to_token.end()) {
        return Token(it->second, lexeme, this->line);
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

bool Scanner::is_eof() { return this->current == this->source.length() - 1; }

char Scanner::advance() { return this->source[this->current++]; }

char Scanner::peek() { return this->source[this->current]; }
