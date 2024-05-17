//
// Created by mihael on 5/2/24.
//

#include "OnlineSchedulingAlgorithmCluster.h"
#include <utility>

OnlineSchedulingAlgorithmCluster::OnlineSchedulingAlgorithmCluster(Topology* topology, std::map<long, OnlineSchedulingAlgorithm*> algorithms) {
    this->topology = topology;
    this->algorithms = std::move(algorithms);
    for (auto [machine_id, algorithm] : this->algorithms) {
        algorithm->setInputs(topology->getTopologyElementsMap().at(machine_id)->getGeneralTopologyElementType());
    }
}

Genotype* OnlineSchedulingAlgorithmCluster::copy() {
    return new OnlineSchedulingAlgorithmCluster(topology, algorithms);
}

Topology* OnlineSchedulingAlgorithmCluster::getTopology() {
    return topology;
}

OnlineSchedulingAlgorithm* OnlineSchedulingAlgorithmCluster::getAlgorithm(long machine_id) {
    return algorithms[machine_id];
}

void OnlineSchedulingAlgorithmCluster::setAlgorithm(long machine_id, OnlineSchedulingAlgorithm* algorithm) {
    algorithm->setInputs(topology->getTopologyElementsMap().at(machine_id)->getGeneralTopologyElementType());
    algorithms[machine_id] = algorithm;
}

