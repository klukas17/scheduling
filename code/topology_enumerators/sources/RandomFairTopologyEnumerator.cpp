//
// Created by mihael on 5/9/24.
//

#include "RandomFairTopologyEnumerator.h"
#include <climits>

RandomFairTopologyEnumerator::RandomFairTopologyEnumerator(Topology* topology, int partition_size) : TopologyEnumerator(topology) {
    this->partition_size = partition_size;
    this->choice_generator = new UniformIntDistributionGenerator(0, INT_MAX);
    createPartitions();
}

RandomFairTopologyEnumerator::~RandomFairTopologyEnumerator() {
    delete choice_generator;
}

std::set<long> RandomFairTopologyEnumerator::getPartition() {
    if (partition_index == partitions.size()) {
        createPartitions();
    }
    int index = partition_index;
    partition_index += 1;
    return partitions[index];
}

void RandomFairTopologyEnumerator::createPartitions() {
    std::vector<std::set<long>> new_partitions;
    auto candidates = machines_with_algorithms;
    while (!candidates.empty()) {
        std::set<long> result;
        while (result.size() < partition_size && !candidates.empty()) {
            int index = choice_generator->generate() % candidates.size();
            auto it = std::begin(candidates);
            std::advance(it, index);
            result.insert(*it);
            candidates.erase(*it);
        }
        new_partitions.push_back(result);
    }
    partitions = new_partitions;
    partition_index = 0;
}


