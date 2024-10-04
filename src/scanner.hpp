#pragma once

#include <string>

#include "token.hpp"

class Scanner {
public:
    Scanner(const std::string &source) : source(source), start(0), current(0), line(0) {};

    Token read_token();

private:
    const std::string &source;
    int start;
    int current;
    int line;

    Token number();
    Token identifier();
    void skip_whitespace();
    char advance();
    char peek() const;
    bool is_eof() const;
};
