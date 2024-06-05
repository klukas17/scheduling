//
// Created by mihael on 5/6/24.
//

#ifndef BASICTOPOLOGYENUMERATOR_H
#define BASICTOPOLOGYENUMERATOR_H
#include "TopologyEnumerator.h"


class BasicTopologyEnumerator final : public TopologyEnumerator {
public:
    explicit BasicTopologyEnumerator(Topology* topology);
    ~BasicTopologyEnumerator();
    std::set<long> getPartition() override;
};



#endif //BASICTOPOLOGYENUMERATOR_H
