#include <fstream>
#include <iostream>

#include "src/scanner.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./compile <filename>" << std::endl;
        return -1;
    }

    std::ifstream file(argv[1]);
    std::string source((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));

    std::cout << source << std::endl;

    Scanner *s = new Scanner(source);
    s->read_tokens();
}
