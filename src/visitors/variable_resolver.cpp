#include <stdexcept>

#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"

#include "visitors.hpp"

void VariableResolver::declare_variable(const Token token) {
    VariableResolverEnvironment *top_level_env = this->environments.at(this->environments.size() - 1);
    top_level_env->declare_variable(token);
}

bool VariableResolver::variable_exists(const Token token) {
    for (int i = this->environments.size() - 1; i >= 0; i--) {
        VariableResolverEnvironment *env = this->environments.at(i);

        if (env->variable_exists(token))
            return true;
    }

    return false;
}

bool VariableResolver::can_declare(const Token token) { return !this->environments.back()->variable_exists(token); }

void VariableResolver::visit_program(const Program &node) {
    for (auto &stmt : node.statements()) {
        stmt->accept(*this);
    }
}

void VariableResolver::visit_declaration_statement(const Declaration &node) {
    if (!can_declare(node.name())) {
        throw std::runtime_error("Variable '" + node.name().lexeme + "' was declared more than once.");
    }

    declare_variable(node.name());

    environments.push_back(new VariableResolverEnvironment(&node));
    node.expression()->accept(*this);
    delete environments.back();
    environments.pop_back();
}

void VariableResolver::visit_assignment_expression(const Assignment &node) {
    if (dynamic_cast<const ExpressionStatement *>(environments.back()->parent()) == nullptr) {
        throw std::runtime_error("Assignment must occur at the top level of the program.");
    }

    if (!variable_exists(node.name())) {
        throw std::runtime_error("Attempted to assign variable '" + node.name().lexeme + "' which does not yet exist.");
    }

    environments.push_back(new VariableResolverEnvironment(&node));
    node.expression()->accept(*this);
    delete environments.back();
    environments.pop_back();
}

void VariableResolver::visit_print_statement(const Print &node) {
    environments.push_back(new VariableResolverEnvironment(&node));
    node.expression()->accept(*this);
    delete environments.back();
    environments.pop_back();
}

void VariableResolver::visit_expression_statement(const ExpressionStatement &node) {
    environments.push_back(new VariableResolverEnvironment(&node));
    node.expression()->accept(*this);
    delete environments.back();
    environments.pop_back();
}

void VariableResolver::visit_block_statement(const Block &node) {
    environments.push_back(new VariableResolverEnvironment(&node));
    for (auto &stmt : node.statements()) {
        stmt->accept(*this);
    }
    delete environments.back();
    environments.pop_back();
}

void VariableResolver::visit_binary_expression(const Binary &node) {
    environments.push_back(new VariableResolverEnvironment(&node));
    node.left()->accept(*this);
    node.right()->accept(*this);
    delete environments.back();
    environments.pop_back();
}

void VariableResolver::visit_unary_expression(const Unary &node) {
    environments.push_back(new VariableResolverEnvironment(&node));
    node.expression()->accept(*this);
    delete environments.back();
    environments.pop_back();
}

void VariableResolver::visit_grouping_expression(const Grouping &node) {
    environments.push_back(new VariableResolverEnvironment(&node));
    node.expression()->accept(*this);
    delete environments.back();
    environments.pop_back();
}

void VariableResolver::visit_number_expression(const Number &node) {}

void VariableResolver::visit_variable_expression(const Variable &node) {
    if (!variable_exists(node.name())) {
        throw std::runtime_error("Variable '" + node.name().to_string() + "' is not yet declared.");
    }
}
