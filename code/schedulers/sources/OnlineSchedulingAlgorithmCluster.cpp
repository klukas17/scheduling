//
// Created by mihael on 5/2/24.
//

#include "OnlineSchedulingAlgorithmCluster.h"

#include <ranges>
#include <utility>

OnlineSchedulingAlgorithmCluster::OnlineSchedulingAlgorithmCluster(Topology* topology, std::map<long, OnlineSchedulingAlgorithm*> algorithms) {
    this->topology = topology;
    this->algorithms = std::move(algorithms);
    for (auto [machine_id, algorithm] : this->algorithms) {
        algorithm->setInputs(topology->getTopologyElementsMap().at(machine_id)->getGeneralTopologyElementType());
    }
}

OnlineSchedulingAlgorithmCluster::~OnlineSchedulingAlgorithmCluster() {
    for (auto algorithm_id : algorithms | std::views::keys) {
        delete algorithms[algorithm_id];
    }
}

Genotype* OnlineSchedulingAlgorithmCluster::copy() {
    std::map<long, OnlineSchedulingAlgorithm*> algorithms_copy;
    for (auto [algorithm_id, algorithm] : algorithms) {
        algorithms_copy[algorithm_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(algorithm->copy());
    }
    return new OnlineSchedulingAlgorithmCluster(topology, algorithms_copy);
}

Topology* OnlineSchedulingAlgorithmCluster::getTopology() {
    return topology;
}

OnlineSchedulingAlgorithm* OnlineSchedulingAlgorithmCluster::getAlgorithm(long machine_id) {
    return algorithms[machine_id];
}

std::map<long, OnlineSchedulingAlgorithm*> OnlineSchedulingAlgorithmCluster::getAlgorithms() {
    return algorithms;
}

void OnlineSchedulingAlgorithmCluster::setAlgorithm(long machine_id, OnlineSchedulingAlgorithm* algorithm) {
    algorithm->setInputs(topology->getTopologyElementsMap().at(machine_id)->getGeneralTopologyElementType());
    algorithms[machine_id] = algorithm;
}

