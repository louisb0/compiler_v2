#pragma once

#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class TacInstruction;

class Program;
class Declaration;
class Assignment;
class Print;
class ExpressionStatement;
class Binary;
class Unary;
class Grouping;
class Number;
class Variable;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visit_program(const Program &node) = 0;
    virtual void visit_declaration(const Declaration &node) = 0;
    virtual void visit_assignment_statement(const Assignment &node) = 0;
    virtual void visit_print_statement(const Print &node) = 0;
    virtual void visit_expression_statement(const ExpressionStatement &node) = 0;
    virtual void visit_binary_expression(const Binary &node) = 0;
    virtual void visit_unary_expression(const Unary &node) = 0;
    virtual void visit_grouping_expression(const Grouping &node) = 0;
    virtual void visit_number_expression(const Number &node) = 0;
    virtual void visit_variable_expression(const Variable &node) = 0;
};

class SyntaxTreePrinter : public Visitor {
public:
    SyntaxTreePrinter() : node_count(0) { graph << "graph TD" << std::endl; }

    void write_to(const std::string &filename);

    void visit_program(const Program &node) override;
    void visit_declaration(const Declaration &node) override;
    void visit_assignment_statement(const Assignment &node) override;
    void visit_print_statement(const Print &node) override;
    void visit_expression_statement(const ExpressionStatement &node) override;
    void visit_binary_expression(const Binary &node) override;
    void visit_unary_expression(const Unary &node) override;
    void visit_grouping_expression(const Grouping &node) override;
    void visit_number_expression(const Number &node) override;
    void visit_variable_expression(const Variable &node) override;

private:
    std::stringstream graph;
    std::vector<int> stack;
    int node_count;

    std::string create_node(const std::string &label);
};

class TacGenerator : public Visitor {
public:
    std::vector<TacInstruction> instructions;

    void visit_program(const Program &node) override;
    void visit_declaration(const Declaration &node) override;
    void visit_assignment_statement(const Assignment &node) override;
    ;
    void visit_print_statement(const Print &node) override;
    void visit_expression_statement(const ExpressionStatement &node) override;
    void visit_binary_expression(const Binary &node) override;
    void visit_unary_expression(const Unary &node) override;
    void visit_grouping_expression(const Grouping &node) override;
    void visit_number_expression(const Number &node) override;
    void visit_variable_expression(const Variable &node) override;

private:
    std::unordered_map<std::string, int> variable_location;
};
