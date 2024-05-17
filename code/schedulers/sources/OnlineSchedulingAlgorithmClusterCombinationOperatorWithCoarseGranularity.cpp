//
// Created by mihael on 5/6/24.
//

#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity.h"
#include "OnlineSchedulingAlgorithmCluster.h"
#include <utility>
#include "UniformIntDistributionGenerator.h"

OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity::OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(CombinationOperator* algorithm_combination_operator) : OnlineSchedulingAlgorithmClusterCombinationOperator(algorithm_combination_operator) {}

Genotype* OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity::combine(Genotype* genotype1, Genotype* genotype2) {
    auto online_scheduling_algorithm_cluster1 = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(genotype1);
    auto online_scheduling_algorithm_cluster2 = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(genotype2);
    std::map<long, OnlineSchedulingAlgorithm*> algorithms;
    auto topology = online_scheduling_algorithm_cluster1->getTopology();
    OnlineSchedulingAlgorithmCluster* parent_algorithm_cluster_to_copy = nullptr;
    auto index = generator->generate();
    if (index == 0) {
        parent_algorithm_cluster_to_copy = online_scheduling_algorithm_cluster1;
    } else {
        parent_algorithm_cluster_to_copy = online_scheduling_algorithm_cluster2;
    }
    for (auto [machine_id, _] : topology->getTopologyElementsMap()) {
        if (modifiable_machines.contains(machine_id)) {
            auto algorithm1 = online_scheduling_algorithm_cluster1->getAlgorithm(machine_id);
            auto algorithm2 = online_scheduling_algorithm_cluster2->getAlgorithm(machine_id);
            auto new_algorithm = algorithm_combination_operator->combine(algorithm1, algorithm2);
            algorithms[machine_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(new_algorithm);
        } else {
            auto algorithm = parent_algorithm_cluster_to_copy->getAlgorithm(machine_id);
            algorithms[machine_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(algorithm->copy());
        }
    }
    return new OnlineSchedulingAlgorithmCluster(topology, algorithms);
}
