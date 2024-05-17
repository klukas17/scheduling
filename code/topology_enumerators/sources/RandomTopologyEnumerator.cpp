//
// Created by mihael on 5/9/24.
//

#include "RandomTopologyEnumerator.h"
#include <climits>

RandomTopologyEnumerator::RandomTopologyEnumerator(Topology* topology, int partition_size) : TopologyEnumerator(topology) {
    this->partition_size = partition_size;
    this->choice_generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

std::set<long> RandomTopologyEnumerator::getPartition() {
    auto candidates = machines_with_algorithms;
    std::set<long> result;
    while (result.size() < partition_size && !candidates.empty()) {
        int index = choice_generator->generate() % candidates.size();
        auto it = std::begin(candidates);
        std::advance(it, index);
        result.insert(*it);
        candidates.erase(*it);
    }
    return result;
}

