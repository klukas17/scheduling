//
// Created by mihael on 5/5/24.
//

#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity.h"
#include "OnlineSchedulingAlgorithmCluster.h"
#include <utility>
#include "UniformIntDistributionGenerator.h"

OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity::OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity(CombinationOperator* algorithm_combination_operator) : OnlineSchedulingAlgorithmClusterCombinationOperator(algorithm_combination_operator) {}

Genotype* OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity::combine(Genotype* genotype1, Genotype* genotype2) {
    auto online_scheduling_algorithm_cluster1 = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(genotype1);
    auto online_scheduling_algorithm_cluster2 = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(genotype2);
    std::map<long, OnlineSchedulingAlgorithm*> algorithms;
    auto topology = online_scheduling_algorithm_cluster1->getTopology();
    for (auto [machine_id, _] : topology->getTopologyElementsMap()) {
        auto algorithm1 = online_scheduling_algorithm_cluster1->getAlgorithm(machine_id);
        auto algorithm2 = online_scheduling_algorithm_cluster2->getAlgorithm(machine_id);
        if (modifiable_machines.contains(machine_id)) {
            auto new_algorithm = algorithm_combination_operator->combine(algorithm1, algorithm2);
            algorithms[machine_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(new_algorithm);
        } else {
            auto index = generator->generate();
            if (index == 0) {
                algorithms[machine_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(algorithm1->copy());
            } else {
                algorithms[machine_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(algorithm2->copy());
            }
        }
    }
    return new OnlineSchedulingAlgorithmCluster(topology, algorithms);
}


