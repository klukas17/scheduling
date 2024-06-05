//
// Created by mihael on 5/9/24.
//

#ifndef RANDOMTOPOLOGYENUMERATOR_H
#define RANDOMTOPOLOGYENUMERATOR_H
#include "TopologyEnumerator.h"
#include "UniformIntDistributionGenerator.h"


class RandomTopologyEnumerator final : public TopologyEnumerator {
    int partition_size;
    UniformIntDistributionGenerator* choice_generator;
public:
    RandomTopologyEnumerator(Topology* topology, int partition_size);
    ~RandomTopologyEnumerator();
    std::set<long> getPartition() override;
};



#endif //RANDOMTOPOLOGYENUMERATOR_H
