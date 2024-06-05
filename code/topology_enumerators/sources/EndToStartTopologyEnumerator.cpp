//
// Created by mihael on 5/9/24.
//

#include "EndToStartTopologyEnumerator.h"

EndToStartTopologyEnumerator::EndToStartTopologyEnumerator(Topology* topology, int partition_size) : TopologyEnumerator(topology) {
    auto traversal_order = topology->getMachineTraversalOrder();
    std::vector<long> machines;
    for (auto machine_id : traversal_order) {
        if (machines_with_algorithms.contains(machine_id)) {
            machines.push_back(machine_id);
        }
    }
    auto machines_size = machines.size();
    int index = machines_size - 1;
    while (index >= 0) {
        std::set<long> partition;
        for (int j = 0; j < partition_size; j++) {
            if (index - j >= 0) {
                partition.insert(machines[index - j]);
            }
        }
        index -= partition_size;
        partitions.push_back(partition);
    }
    partition_index = 0;
}

EndToStartTopologyEnumerator::~EndToStartTopologyEnumerator() = default;

std::set<long> EndToStartTopologyEnumerator::getPartition() {
    int index = partition_index;
    partition_index = (partition_index + 1) % partitions.size();
    return partitions[index];
}

