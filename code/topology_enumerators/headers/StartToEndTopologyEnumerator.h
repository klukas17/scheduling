//
// Created by mihael on 5/9/24.
//

#ifndef STARTTOENDTOPOLOGYENUMERATOR_H
#define STARTTOENDTOPOLOGYENUMERATOR_H
#include "TopologyEnumerator.h"


class StartToEndTopologyEnumerator final : public TopologyEnumerator {
    std::vector<std::set<long>> partitions;
    int partition_index;
public:
    StartToEndTopologyEnumerator(Topology* topology, int partition_size);
    ~StartToEndTopologyEnumerator();
    std::set<long> getPartition() override;
};



#endif //STARTTOENDTOPOLOGYENUMERATOR_H
