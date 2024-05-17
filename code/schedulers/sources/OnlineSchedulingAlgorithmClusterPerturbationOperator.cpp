//
// Created by mihael on 5/5/24.
//

#include "OnlineSchedulingAlgorithmClusterPerturbationOperator.h"
#include <utility>
#include "OnlineSchedulingAlgorithmCluster.h"

OnlineSchedulingAlgorithmClusterPerturbationOperator::OnlineSchedulingAlgorithmClusterPerturbationOperator(PerturbationOperator* algorithm_perturbation_operator) {
    this->algorithm_perturbation_operator = algorithm_perturbation_operator;
}

void OnlineSchedulingAlgorithmClusterPerturbationOperator::setModifiableMachines(std::set<long> machines) {
    this->modifiable_machines = std::move(machines);
}

void OnlineSchedulingAlgorithmClusterPerturbationOperator::perturbate(Genotype* genotype) {
    auto online_scheduling_algorithm_cluster = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(genotype);
    for (auto machine_id : modifiable_machines) {
        algorithm_perturbation_operator->perturbate(online_scheduling_algorithm_cluster->getAlgorithm(machine_id));
    }
}
