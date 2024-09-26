#include <iostream>

#include "scanner.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./compile <filename>" << std::endl;
        return -1;
    }

    Scanner *s = new Scanner(argv[1]);
    delete s;
}
