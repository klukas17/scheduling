//
// Created by mihael on 5/5/24.
//

#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"

#include "ConstantProgramming.h"
#include "OnlineSchedulingAlgorithm.h"
#include "OnlineSchedulingAlgorithmCluster.h"

OnlineSchedulingAlgorithmClusterCreationOperator::OnlineSchedulingAlgorithmClusterCreationOperator(GenotypeBlueprint* genotype_blueprint, CreationOperator* algorithm_creation_operator) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<OnlineSchedulingAlgorithmClusterGenotypeBlueprint*>(genotype_blueprint);
    this->algorithm_creation_operator = algorithm_creation_operator;
}

Genotype* OnlineSchedulingAlgorithmClusterCreationOperator::create() {
    std::map<long, OnlineSchedulingAlgorithm*> algorithms;
    for (auto element_id : blueprint->topology_elements_with_algorithms) {
        algorithms[element_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(algorithm_creation_operator->create());
    }
    for (auto element_id : blueprint->topology_elements_without_algorithms) {
        algorithms[element_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(new ConstantProgramming(0));
    }
    return new OnlineSchedulingAlgorithmCluster(blueprint->topology, algorithms);
}
