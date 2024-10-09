#pragma once

#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../token.hpp"

class TacInstruction;

class Node;

class Program;
class ExpressionStatement;
class Block;
class Declaration;
class Print;

class Assignment;
class Variable;
class Binary;
class Unary;
class Grouping;
class Number;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visit_program(const Program &node) = 0;
    virtual void visit_expression_statement(const ExpressionStatement &node) = 0;
    virtual void visit_block_statement(const Block &node) = 0;
    virtual void visit_declaration_statement(const Declaration &node) = 0;
    virtual void visit_print_statement(const Print &node) = 0;

    virtual void visit_assignment_expression(const Assignment &node) = 0;
    virtual void visit_variable_expression(const Variable &node) = 0;
    virtual void visit_binary_expression(const Binary &node) = 0;
    virtual void visit_unary_expression(const Unary &node) = 0;
    virtual void visit_grouping_expression(const Grouping &node) = 0;
    virtual void visit_number_expression(const Number &node) = 0;
};

class SyntaxTreePrinter : public Visitor {
public:
    SyntaxTreePrinter() : node_count(0) { graph << "graph TD" << std::endl; }

    void write_to(const std::string &filename);

    void visit_program(const Program &node) override;
    void visit_expression_statement(const ExpressionStatement &node) override;
    void visit_block_statement(const Block &node) override;
    void visit_declaration_statement(const Declaration &node) override;
    void visit_print_statement(const Print &node) override;

    void visit_assignment_expression(const Assignment &node) override;
    void visit_variable_expression(const Variable &node) override;
    void visit_binary_expression(const Binary &node) override;
    void visit_unary_expression(const Unary &node) override;
    void visit_grouping_expression(const Grouping &node) override;
    void visit_number_expression(const Number &node) override;

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
    void visit_expression_statement(const ExpressionStatement &node) override;
    void visit_block_statement(const Block &node) override;
    void visit_declaration_statement(const Declaration &node) override;
    void visit_print_statement(const Print &node) override;

    void visit_assignment_expression(const Assignment &node) override;
    void visit_variable_expression(const Variable &node) override;
    void visit_binary_expression(const Binary &node) override;
    void visit_unary_expression(const Unary &node) override;
    void visit_grouping_expression(const Grouping &node) override;
    void visit_number_expression(const Number &node) override;

private:
    std::vector<std::unordered_map<std::string, int>> variable_location_stack;
};

class VariableResolverEnvironment {
public:
    VariableResolverEnvironment(const Node *parent_node) : parent_node(parent_node) {}

    const Node *parent() { return parent_node; }
    void declare_variable(const Token token) { declared_variables.insert(token.lexeme); }
    bool variable_exists(const Token token) {
        return declared_variables.find(token.lexeme) != declared_variables.end();
    }

private:
    const Node *parent_node;
    std::unordered_set<std::string> declared_variables;
};

class VariableResolver : public Visitor {
public:
    VariableResolver() { environments.push_back(new VariableResolverEnvironment(nullptr)); }
    ~VariableResolver() { delete environments.at(0); }

    void visit_program(const Program &node) override;
    void visit_expression_statement(const ExpressionStatement &node) override;
    void visit_block_statement(const Block &node) override;
    void visit_declaration_statement(const Declaration &node) override;
    void visit_print_statement(const Print &node) override;

    void visit_assignment_expression(const Assignment &node) override;
    void visit_variable_expression(const Variable &node) override;
    void visit_binary_expression(const Binary &node) override;
    void visit_unary_expression(const Unary &node) override;
    void visit_grouping_expression(const Grouping &node) override;
    void visit_number_expression(const Number &node) override;

private:
    std::vector<VariableResolverEnvironment *> environments;

    void declare_variable(const Token token);
    bool variable_exists(const Token token);
    bool can_declare(const Token token);
};
