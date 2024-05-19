//
// Created by mihael on 5/2/24.
//

#ifndef ONLINESCHEDULINGALGORITHMCLUSTER_H
#define ONLINESCHEDULINGALGORITHMCLUSTER_H

#include <map>

#include "Genotype.h"
#include "OnlineSchedulingAlgorithm.h"
#include "Topology.h"


class OnlineSchedulingAlgorithmCluster final : public Genotype {
    Topology* topology;
    std::map<long, OnlineSchedulingAlgorithm*> algorithms;
public:
    OnlineSchedulingAlgorithmCluster(Topology* topology, std::map<long, OnlineSchedulingAlgorithm*> algorithms);
    ~OnlineSchedulingAlgorithmCluster();
    Genotype* copy() override;
    Topology* getTopology();
    OnlineSchedulingAlgorithm* getAlgorithm(long machine_id);
    void setAlgorithm(long machine_id, OnlineSchedulingAlgorithm* algorithm);
};



#endif //ONLINESCHEDULINGALGORITHMCLUSTER_H
