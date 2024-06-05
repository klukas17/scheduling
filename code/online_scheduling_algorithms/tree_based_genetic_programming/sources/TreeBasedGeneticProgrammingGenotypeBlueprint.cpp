//
// Created by mihael on 5/21/24.
//

#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"

TreeBasedGeneticProgrammingGenotypeBlueprint::TreeBasedGeneticProgrammingGenotypeBlueprint(TBGPNodeFactory* node_factory, int max_height) {
    this->node_factory = node_factory;
    this->max_height = max_height;
}

TreeBasedGeneticProgrammingGenotypeBlueprint::~TreeBasedGeneticProgrammingGenotypeBlueprint() {
    delete node_factory;
}

void TreeBasedGeneticProgrammingGenotypeBlueprint::setInputs(std::vector<std::string> inputs) {
    this->inputs = inputs;
    this->node_factory->setInputs(inputs);
}
