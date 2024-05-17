//
// Created by mihael on 5/6/24.
//

#ifndef TOPOLOGYENUMERATOR_H
#define TOPOLOGYENUMERATOR_H

#include "Topology.h"

class TopologyEnumerator {
protected:
    Topology* topology;
    std::set<long> machines_with_algorithms;
public:
    explicit TopologyEnumerator(Topology* topology);
    virtual std::set<long> getPartition() = 0;
    virtual ~TopologyEnumerator() = 0;
};



#endif //TOPOLOGYENUMERATOR_H
