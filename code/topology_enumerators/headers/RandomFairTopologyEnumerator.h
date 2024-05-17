//
// Created by mihael on 5/9/24.
//

#ifndef RANDOMFAIRTOPOLOGYENUMERATOR_H
#define RANDOMFAIRTOPOLOGYENUMERATOR_H
#include "TopologyEnumerator.h"
#include "UniformIntDistributionGenerator.h"


class RandomFairTopologyEnumerator final : public TopologyEnumerator {
    int partition_size;
    int partition_index;
    std::vector<std::set<long>> partitions;
    UniformIntDistributionGenerator* choice_generator;
    void createPartitions();
public:
    RandomFairTopologyEnumerator(Topology* topology, int partition_size);
    std::set<long> getPartition() override;
};



#endif //RANDOMFAIRTOPOLOGYENUMERATOR_H
