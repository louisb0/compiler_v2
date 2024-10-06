#include <fstream>
#include <iostream>
#include <memory>

#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"

#include "visitors.hpp"

void SyntaxTreePrinter::write_to(const std::string &filename) {
    std::ofstream out_file(filename);
    out_file << graph.str();
    out_file.close();
}

std::string SyntaxTreePrinter::create_node(const std::string &label) {
    int current_node = node_count++;

    std::string node_id = "node" + std::to_string(current_node);
    graph << node_id << "[\"" << label << "\"]\n";

    if (!stack.empty()) {
        int parent_node = stack.back();
        graph << "node" << parent_node << " --> " << node_id << "\n";
    }

    return node_id;
}

void SyntaxTreePrinter::visit_program(const Program &node) {
    std::string node_id = create_node("Program");

    stack.push_back(node_count - 1);
    for (auto &stmt : node.statements()) {
        stmt->accept(*this);
    }
    stack.pop_back();
};

void SyntaxTreePrinter::visit_declaration_statement(const Declaration &node) {
    std::string node_id = create_node("Declaration");

    stack.push_back(node_count - 1);
    create_node(node.name().lexeme);
    create_node("i32");
    node.expression()->accept(*this);
    stack.pop_back();
}

void SyntaxTreePrinter::visit_assignment_expression(const Assignment &node) {
    std::string node_id = create_node("Assignment");

    stack.push_back(node_count - 1);
    create_node(node.name().lexeme);
    node.expression()->accept(*this);
    stack.pop_back();
};

void SyntaxTreePrinter::visit_print_statement(const Print &node) {
    std::string node_id = create_node("Print");

    stack.push_back(node_count - 1);
    node.expression()->accept(*this);
    stack.pop_back();
}

void SyntaxTreePrinter::visit_expression_statement(const ExpressionStatement &node) {
    std::string node_id = create_node("ExpressionStatement");

    stack.push_back(node_count - 1);
    node.expression()->accept(*this);
    stack.pop_back();
}

void SyntaxTreePrinter::visit_binary_expression(const Binary &node) {
    std::string node_id = create_node(node.symbol().lexeme);

    stack.push_back(node_count - 1);
    node.left()->accept(*this);
    node.right()->accept(*this);
    stack.pop_back();
}

void SyntaxTreePrinter::visit_unary_expression(const Unary &node) {
    std::string node_id = create_node(node.symbol().lexeme);

    stack.push_back(node_count - 1);
    node.expression()->accept(*this);
    stack.pop_back();
}

void SyntaxTreePrinter::visit_grouping_expression(const Grouping &node) {
    std::string node_id = create_node("Grouping");

    stack.push_back(node_count - 1);
    node.expression()->accept(*this);
    stack.pop_back();
}

void SyntaxTreePrinter::visit_number_expression(const Number &node) { create_node(std::to_string(node.value())); }

void SyntaxTreePrinter::visit_variable_expression(const Variable &node) { create_node(node.name().lexeme); }
