#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

#include "token.hpp"

class Scanner {
  public:
    Scanner(const std::string &source)
        : source(source), start(0), current(0), line(0) {};

    std::vector<Token> read_tokens();

  private:
    std::string source;
    int start;
    int current;
    int line;

    Token read_token();
    Token number();
    Token identifier();
    void skip_whitespace();
    bool is_eof();
    char advance();
    char peek();
};

#endif
