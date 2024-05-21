//
// Created by mihael on 5/5/24.
//

#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"

#include "ConstantProgramming.h"
#include "OnlineSchedulingAlgorithm.h"
#include "OnlineSchedulingAlgorithmCluster.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"

OnlineSchedulingAlgorithmClusterCreationOperator::OnlineSchedulingAlgorithmClusterCreationOperator(GenotypeBlueprint* genotype_blueprint, CreationOperator* algorithm_creation_operator) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<OnlineSchedulingAlgorithmClusterGenotypeBlueprint*>(genotype_blueprint);
    this->algorithm_creation_operator = algorithm_creation_operator;
}

Genotype* OnlineSchedulingAlgorithmClusterCreationOperator::create() {
    std::map<long, OnlineSchedulingAlgorithm*> algorithms;
    auto algorithm_blueprint = dynamic_cast<OnlineSchedulingAlgorithmGenotypeBlueprint*>(algorithm_creation_operator->genotype_blueprint);
    algorithm_blueprint->setInputs(OnlineSchedulingAlgorithm::group_inputs);
    for (auto element_id : blueprint->topology_elements_with_algorithms_in_inner_nodes) {
        algorithms[element_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(algorithm_creation_operator->create());
    }
    algorithm_blueprint->setInputs(OnlineSchedulingAlgorithm::machine_inputs);
    for (auto element_id : blueprint->topology_elements_with_algorithms_in_leaves) {
        algorithms[element_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(algorithm_creation_operator->create());
    }
    for (auto element_id : blueprint->topology_elements_without_algorithms) {
        algorithms[element_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(new ConstantProgramming(0));
    }
    return new OnlineSchedulingAlgorithmCluster(blueprint->topology, algorithms);
}
