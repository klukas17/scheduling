//
// Created by mihael on 5/9/24.
//

#ifndef ENDTOSTARTTOPOLOGYENUMERATOR_H
#define ENDTOSTARTTOPOLOGYENUMERATOR_H
#include "TopologyEnumerator.h"


class EndToStartTopologyEnumerator final : public TopologyEnumerator {
    std::vector<std::set<long>> partitions;
    int partition_index;
public:
    EndToStartTopologyEnumerator(Topology* topology, int partition_size);
    std::set<long> getPartition() override;
};



#endif //ENDTOSTARTTOPOLOGYENUMERATOR_H
