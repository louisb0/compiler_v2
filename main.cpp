#include <fstream>
#include <iostream>

#include "src/parser.hpp"
#include "src/visitors/print_visitor.hpp"
#include "src/visitors/tac_generator.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./compile <filename>" << std::endl;
        return -1;
    }

    std::ifstream file(argv[1]);
    std::string source((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    std::cout << source << std::endl;

    Parser *p = new Parser(source);
    std::unique_ptr<Statement> stmt = p->parse_statement();

    PrintVisitor *v = new PrintVisitor();
    stmt->accept(*v);

    std::cout << std::endl;

    TacGenerator *t = new TacGenerator();
    stmt->accept(*t);

    for (int i = 0; i < t->instructions.size(); i++) {
        std::cout << t->instructions.at(i).str(i) << std::endl;
    }

    delete p;
    delete v;
    delete t;
}
