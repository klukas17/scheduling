//
// Created by mihael on 5/5/24.
//

#ifndef ONLINESCHEDULINGALGORITHMCLUSTERGENOTYPEBLUEPRINT_H
#define ONLINESCHEDULINGALGORITHMCLUSTERGENOTYPEBLUEPRINT_H

#include "GenotypeBlueprint.h"
#include "Topology.h"


class OnlineSchedulingAlgorithmClusterGenotypeBlueprint final : public GenotypeBlueprint {
public:
    Topology* topology;
    std::set<long> topology_elements_with_algorithms_in_inner_nodes;
    std::set<long> topology_elements_with_algorithms_in_leaves;
    std::set<long> topology_elements_without_algorithms;
    explicit OnlineSchedulingAlgorithmClusterGenotypeBlueprint(Topology* topology);
};



#endif //ONLINESCHEDULINGALGORITHMCLUSTERGENOTYPEBLUEPRINT_H
