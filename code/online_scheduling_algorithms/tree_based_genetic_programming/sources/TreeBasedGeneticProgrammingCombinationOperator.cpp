//
// Created by mihael on 5/21/24.
//

#include "TreeBasedGeneticProgrammingCombinationOperator.h"
#include <climits>

#include "TBGPNodeCollector.h"
#include "TBGPNodeDepthAdjuster.h"
#include "TBGPNodeReplacer.h"
#include "TreeBasedGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"

TreeBasedGeneticProgrammingCombinationOperator::TreeBasedGeneticProgrammingCombinationOperator(TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

TreeBasedGeneticProgrammingCombinationOperator::~TreeBasedGeneticProgrammingCombinationOperator() {
    delete generator;
}

Genotype* TreeBasedGeneticProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto tbgp1 = dynamic_cast<TreeBasedGeneticProgramming*>(genotype1);
    auto tbgp2 = dynamic_cast<TreeBasedGeneticProgramming*>(genotype2);

    auto tbgp = dynamic_cast<TreeBasedGeneticProgramming*>(tbgp1->copy());
    auto parent1_candidates = TBGPNodeCollector::collect(tbgp, blueprint->max_height);
    auto parent1_candidate_id = generator->generate() % parent1_candidates.size();
    auto parent1_candidate = parent1_candidates[parent1_candidate_id];

    auto parent_2_candidates = TBGPNodeCollector::collect(tbgp2, parent1_candidate->height);
    auto parent2_candidate_id = generator->generate() % parent_2_candidates.size();
    auto parent2_candidate = parent_2_candidates[parent2_candidate_id]->copy();

    parent2_candidate->parent = parent1_candidate->parent;

    if (parent1_candidate->parent == nullptr) {
        tbgp->setRootNode(parent2_candidate);
    } else {
        TBGPNodeReplacer::replaceChildren(parent1_candidate->parent, parent1_candidate, parent2_candidate);
    }

    delete parent1_candidate;

    TBGPNodeDepthAdjuster::adjustDepths(tbgp, blueprint->max_height);

    return tbgp;
}

