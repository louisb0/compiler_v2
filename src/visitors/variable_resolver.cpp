#include <stdexcept>

#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"

#include "visitors.hpp"

void VariableResolver::visit_program(const Program &node) {
    for (auto &stmt : node.statements()) {
        stmt->accept(*this);
    }
}

void VariableResolver::visit_declaration(const Declaration &node) {
    if (variable_exists(node.name())) {
        throw std::runtime_error("Variable '" + node.name().lexeme + "' was declared more than once.");
    }

    declare_variable(node.name());

    stack.push_back(&node);
    node.expression()->accept(*this);
    stack.pop_back();
}

void VariableResolver::visit_assignment_statement(const Assignment &node) {
    const Node *parent = stack[stack.size() - 1];
    if (dynamic_cast<const ExpressionStatement *>(parent) == nullptr) {
        throw std::runtime_error("Assignment must occur at the top level of the program.");
    }

    if (!variable_exists(node.name())) {
        throw std::runtime_error("Attempted to assign variable '" + node.name().lexeme + "' which does not yet exist.");
    }

    stack.push_back(&node);
    node.expression()->accept(*this);
    stack.pop_back();
}

void VariableResolver::visit_print_statement(const Print &node) {
    stack.push_back(&node);
    node.expression()->accept(*this);
    stack.pop_back();
}

void VariableResolver::visit_expression_statement(const ExpressionStatement &node) {
    stack.push_back(&node);
    node.expression()->accept(*this);
    stack.pop_back();
}

void VariableResolver::visit_binary_expression(const Binary &node) {
    stack.push_back(&node);
    node.left()->accept(*this);
    node.right()->accept(*this);
    stack.pop_back();
}

void VariableResolver::visit_unary_expression(const Unary &node) {
    stack.push_back(&node);
    node.expression()->accept(*this);
    stack.pop_back();
}

void VariableResolver::visit_grouping_expression(const Grouping &node) {
    stack.push_back(&node);
    node.expression()->accept(*this);
    stack.pop_back();
}

void VariableResolver::visit_number_expression(const Number &node) {}

void VariableResolver::visit_variable_expression(const Variable &node) {
    if (!variable_exists(node.name())) {
        throw std::runtime_error("Variable '" + node.name().lexeme + "' is not yet declared.");
    }
}
