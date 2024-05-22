//
// Created by mihael on 5/21/24.
//

#include "TreeBasedGeneticProgramming.h"

TreeBasedGeneticProgramming::TreeBasedGeneticProgramming(TBGPNode* root_node) {
    this->root_node = root_node;
}

TreeBasedGeneticProgramming::~TreeBasedGeneticProgramming() {
    delete root_node;
}

Genotype* TreeBasedGeneticProgramming::copy() {
    auto copy = new TreeBasedGeneticProgramming(root_node->copy());
    copy->setInputs(inputs);
    return copy;
}

TBGPNode* TreeBasedGeneticProgramming::getRootNode() {
    return root_node;
}

void TreeBasedGeneticProgramming::setRootNode(TBGPNode* root_node) {
    this->root_node = root_node;
}

double TreeBasedGeneticProgramming::calculateScore(std::map<std::string, double> params) {
    return root_node->eval(params);
}



