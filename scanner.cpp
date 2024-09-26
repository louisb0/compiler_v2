#include <fstream>
#include <iostream>
#include <sstream>

#include "scanner.hpp"

Scanner::Scanner(const std::string &filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    this->source = buffer.str();
}

Scanner::~Scanner() { std::cout << this->source; }

Token Scanner::read() {}
