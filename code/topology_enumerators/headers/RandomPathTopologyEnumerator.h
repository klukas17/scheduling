//
// Created by mihael on 5/9/24.
//

#ifndef RANDOMPATHTOPOLOGYENUMERATOR_H
#define RANDOMPATHTOPOLOGYENUMERATOR_H
#include "TopologyEnumerator.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"


class RandomPathTopologyEnumerator final : public TopologyEnumerator {
    UniformRealDistributionGenerator* chance_generator;
    UniformIntDistributionGenerator* choice_generator;
    double change_element_chance;
    void traverseTopology(std::set<long>& partition, TopologyElement* element);
public:
    RandomPathTopologyEnumerator(Topology* topology, double change_element_chance);
    std::set<long> getPartition() override;
};



#endif //RANDOMPATHTOPOLOGYENUMERATOR_H
