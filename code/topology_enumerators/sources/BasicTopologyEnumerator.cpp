//
// Created by mihael on 5/6/24.
//

#include "BasicTopologyEnumerator.h"

BasicTopologyEnumerator::BasicTopologyEnumerator(Topology* topology) : TopologyEnumerator(topology) {}

BasicTopologyEnumerator::~BasicTopologyEnumerator() = default;

std::set<long> BasicTopologyEnumerator::getPartition() {
    return machines_with_algorithms;
}
