#include <fstream>
#include <iostream>
#include <ostream>

#include "src/codegen.hpp"
#include "src/parser.hpp"
#include "src/visitors/visitors.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./compile <filename>" << std::endl;
        return -1;
    }

    std::ifstream file(argv[1]);
    std::string source((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    std::cout << source << std::endl;

    Parser *p = new Parser(source);
    std::unique_ptr<Program> program = p->parse();

    SyntaxTreePrinter *v = new SyntaxTreePrinter();
    program->accept(*v);
    v->write_to("ast.mermaid");

    VariableResolver *r = new VariableResolver();
    program->accept(*r);

    TacGenerator *t = new TacGenerator();
    program->accept(*t);

    for (size_t i = 0; i < t->instructions.size(); i++) {
        std::cout << t->instructions.at(i).to_string(i) << std::endl;
    }

    CodeGenerator *g = new CodeGenerator(t->instructions);
    std::string code = g->generate();
    std::cout << code << std::endl;

    std::ofstream out;
    out.open("result.asm");
    out << g->generate();
    out.close();

    delete g;
    delete t;
    delete r;
    delete v;
    delete p;
}
