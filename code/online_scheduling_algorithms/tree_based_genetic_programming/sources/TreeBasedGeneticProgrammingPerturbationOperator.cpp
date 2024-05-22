//
// Created by mihael on 5/21/24.
//

#include "TreeBasedGeneticProgrammingPerturbationOperator.h"
#include <climits>

#include "TBGPNodeCollector.h"
#include "TBGPNodeDepthAdjuster.h"
#include "TBGPNodeReplacer.h"
#include "TreeBasedGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"

TreeBasedGeneticProgrammingPerturbationOperator::TreeBasedGeneticProgrammingPerturbationOperator(TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

void TreeBasedGeneticProgrammingPerturbationOperator::perturbate(Genotype* genotype) {
    auto tbgp = dynamic_cast<TreeBasedGeneticProgramming*>(genotype);
    blueprint->setInputs(tbgp->getInputs());

    auto candidates = TBGPNodeCollector::collect(tbgp, blueprint->max_height);
    auto candidate_id = generator->generate() % candidates.size();
    auto candidate = candidates[candidate_id];
    auto candidate_replacement = blueprint->node_factory->createNode(candidate->max_depth);

    if (candidate->parent == nullptr) {
        tbgp->setRootNode(candidate_replacement);
    } else {
        TBGPNodeReplacer::replaceChildren(candidate->parent, candidate, candidate_replacement);
    }

    delete candidate;

    TBGPNodeDepthAdjuster::adjustDepths(tbgp, blueprint->max_height);

    blueprint->setInputs({});
}

