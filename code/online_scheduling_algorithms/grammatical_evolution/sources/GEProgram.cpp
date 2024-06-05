//
// Created by mihael on 5/30/24.
//

#include "GEProgram.h"

#include <utility>

GEProgram::GEProgram(std::vector<GEGenotypeNode*> genotype_nodes) {
    this->genotype_nodes = std::move(genotype_nodes);
    this->phenotype_root_node = nullptr;
}

GEProgram::GEProgram(std::vector<GEGenotypeNode*> genotype_nodes, GEPhenotypeNode* phenotype_root_node) {
    this->genotype_nodes = std::move(genotype_nodes);
    this->phenotype_root_node = phenotype_root_node;
}

GEProgram::~GEProgram() {
    for (auto & node : genotype_nodes) {
        delete node;
    }
    if (phenotype_root_node != nullptr) {
        delete phenotype_root_node;
    }
}

GEProgram* GEProgram::copy() {
    std::vector<GEGenotypeNode*> nodes_copy;
    nodes_copy.reserve(genotype_nodes.size());
    for (auto node : genotype_nodes) {
        nodes_copy.push_back(node->copy());
    }
    return new GEProgram(nodes_copy, (phenotype_root_node != nullptr) ? phenotype_root_node->copy() : nullptr);
}

std::map<int, double> GEProgram::collectAllConstants() {
    std::map<int, double> constants;
    if (phenotype_root_node != nullptr) {
        phenotype_root_node->collectConstants(constants);
    }
    return constants;
}


double GEProgram::executeProgram(std::map<std::string, double> params) {
    return phenotype_root_node != nullptr ? phenotype_root_node->eval(params) : 0;
}

