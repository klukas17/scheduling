//
// Created by mihael on 5/31/24.
//

#include "SGEProgram.h"

#include <utility>

SGEProgram::SGEProgram(
    SGEProgramMetadata* metadata,
    std::vector<int> symbol_values,
    std::vector<int> terminal_values,
    std::vector<int> nonterminal_values,
    std::vector<int> param_values
) {
    this->metadata = metadata;
    this->symbol_values = std::move(symbol_values);
    this->terminal_values = std::move(terminal_values);
    this->nonterminal_values = std::move(nonterminal_values);
    this->param_values = std::move(param_values);
    this->phenotype_root_node = nullptr;
}

SGEProgram::~SGEProgram() {
    delete metadata;
    delete phenotype_root_node;
}

SGEProgram* SGEProgram::copy() {
    auto program = new SGEProgram(
        metadata->copy(),
        symbol_values,
        terminal_values,
        nonterminal_values,
        param_values
    );
    program->phenotype_root_node = this->phenotype_root_node->copy();
    return program;
}

std::map<int, double> SGEProgram::collectAllConstants() {
    std::map<int, double> constants;
    if (phenotype_root_node != nullptr) {
        phenotype_root_node->collectConstants(constants);
    }
    return constants;
}

double SGEProgram::executeProgram(std::map<std::string, double> params) {
    return phenotype_root_node->eval(params);
}
