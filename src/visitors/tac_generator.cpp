#include <string>
#include <unordered_map>

#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"
#include "../tac_instruction.hpp"

#include "visitors.hpp"

void TacGenerator::visit_program(const Program &node) {
    this->variable_location_stack.push_back(std::unordered_map<std::string, int>());

    for (auto &stmt : node.statements()) {
        stmt->accept(*this);
    }
}

void TacGenerator::visit_declaration_statement(const Declaration &node) {
    node.expression()->accept(*this);

    this->variable_location_stack.back()[node.name().lexeme] = this->instructions.size() - 1;
}

void TacGenerator::visit_assignment_expression(const Assignment &node) {
    int declaration = this->variable_location_stack.back()[node.name().lexeme];
    node.expression()->accept(*this);

    this->instructions.push_back(TacInstruction(TacOperation::ASSIGN, declaration, this->instructions.size() - 1));
};

void TacGenerator::visit_print_statement(const Print &node) {
    node.expression()->accept(*this);

    this->instructions.push_back(TacInstruction(TacOperation::PRINT, this->instructions.size() - 1));
};

void TacGenerator::visit_expression_statement(const ExpressionStatement &node) { node.expression()->accept(*this); };

void TacGenerator::visit_block_statement(const Block &node) {
    this->variable_location_stack.push_back(std::unordered_map<std::string, int>());
    for (auto &stmt : node.statements()) {
        stmt->accept(*this);
    }
    this->variable_location_stack.pop_back();
}

void TacGenerator::visit_binary_expression(const Binary &node) {
    node.left()->accept(*this);
    int leftIndex = this->instructions.size() - 1;

    node.right()->accept(*this);
    int rightIndex = this->instructions.size() - 1;

    TacOperation op;
    switch (node.symbol().lexeme[0]) {
    case '+':
        op = TacOperation::ADD;
        break;
    case '-':
        op = TacOperation::SUB;
        break;
    case '*':
        op = TacOperation::MUL;
        break;
    case '/':
        op = TacOperation::DIV;
        break;
    }

    this->instructions.push_back(TacInstruction(op, leftIndex, rightIndex));
};

void TacGenerator::visit_unary_expression(const Unary &node) {
    node.expression()->accept(*this);

    this->instructions.push_back(TacInstruction(TacOperation::NEG, this->instructions.size() - 1));
}

void TacGenerator::visit_grouping_expression(const Grouping &node) { node.expression()->accept(*this); };

void TacGenerator::visit_number_expression(const Number &node) {
    this->instructions.push_back(TacInstruction(TacOperation::VALUE, node.value()));
}

void TacGenerator::visit_variable_expression(const Variable &node) {
    const std::string &var_name = node.name().lexeme;
    int declaration = -1;

    for (int i = this->variable_location_stack.size() - 1; i >= 0; --i) {
        const auto &scope = this->variable_location_stack[i];
        auto it = scope.find(var_name);
        if (it != scope.end()) {
            declaration = it->second;
            break;
        }
    }

    if (declaration == -1) {
        // unreachable
        throw std::runtime_error("Variable '" + var_name + "' is not declared in this scope.");
    }

    this->instructions.push_back(TacInstruction(TacOperation::VARIABLE, declaration));
}
