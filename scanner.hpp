#ifndef SCANNER_H
#define SCANNER_H

#include <string>

enum class TokenType {
    LET,
    TYPE_I32,
    IDENTIFIER,
    NUMBER,
    LPAREN,
    RPAREN,
    SEMICOLON,
    EQUAL,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PRINT,
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType type, const std::string &lexeme, int line)
        : type(type), lexeme(lexeme), line(line) {}
};

class Scanner {
  public:
    Scanner(const std::string &filename);
    ~Scanner();

    Token read();

  private:
    std::string source;
};

#endif
