//
// Created by mihael on 5/21/24.
//

#include "TreeBasedGeneticProgrammingCreationOperator.h"

#include "TBGPNodeDepthAdjuster.h"
#include "TreeBasedGeneticProgramming.h"

TreeBasedGeneticProgrammingCreationOperator::TreeBasedGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<TreeBasedGeneticProgrammingGenotypeBlueprint*>(genotype_blueprint);
}

TreeBasedGeneticProgrammingCreationOperator::~TreeBasedGeneticProgrammingCreationOperator() = default;

Genotype* TreeBasedGeneticProgrammingCreationOperator::create() {
    auto tbgp = new TreeBasedGeneticProgramming(blueprint->node_factory->createNode(blueprint->max_height));
    TBGPNodeDepthAdjuster::adjustDepths(tbgp, blueprint->max_height);
    tbgp->setInputs(blueprint->getInputs());
    return tbgp;
}
