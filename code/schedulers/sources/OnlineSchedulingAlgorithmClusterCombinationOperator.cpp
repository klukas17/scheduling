//
// Created by mihael on 5/6/24.
//

#include "OnlineSchedulingAlgorithmClusterCombinationOperator.h"
#include "UniformIntDistributionGenerator.h"

OnlineSchedulingAlgorithmClusterCombinationOperator::OnlineSchedulingAlgorithmClusterCombinationOperator(CombinationOperator* algorithm_combination_operator) {
    this->algorithm_combination_operator = algorithm_combination_operator;
    this->generator = new UniformIntDistributionGenerator(0, 1);
}

OnlineSchedulingAlgorithmClusterCombinationOperator::~OnlineSchedulingAlgorithmClusterCombinationOperator() {
    delete generator;
}

void OnlineSchedulingAlgorithmClusterCombinationOperator::setModifiableMachines(std::set<long> machines) {
    this->modifiable_machines = std::move(machines);
}