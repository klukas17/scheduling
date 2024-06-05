//
// Created by mihael on 5/9/24.
//

#include "StartToEndTopologyEnumerator.h"

StartToEndTopologyEnumerator::StartToEndTopologyEnumerator(Topology* topology, int partition_size) : TopologyEnumerator(topology){
    auto traversal_order = topology->getMachineTraversalOrder();
    std::vector<long> machines;
    for (auto machine_id : traversal_order) {
        if (machines_with_algorithms.contains(machine_id)) {
            machines.push_back(machine_id);
        }
    }
    auto machines_size = machines.size();
    int index = 0;
    while (index < machines_size) {
        std::set<long> partition;
        for (int j = 0; j < partition_size; j++) {
            if (index + j < machines_size) {
                partition.insert(machines[index + j]);
            }
        }
        index += partition_size;
        partitions.push_back(partition);
    }
    partition_index = 0;
}

StartToEndTopologyEnumerator::~StartToEndTopologyEnumerator() = default;

std::set<long> StartToEndTopologyEnumerator::getPartition() {
    int index = partition_index;
    partition_index = (partition_index + 1) % partitions.size();
    return partitions[index];
}

