//
// Created by mihael on 01/05/23.
//

#ifndef SCHEDULING_PARALLELGROUPNODE_H
#define SCHEDULING_PARALLELGROUPNODE_H

#include "GroupNode.h"

class ParallelGroupNode final : public GroupNode {
public:
    explicit ParallelGroupNode(long id);
};

#endif //SCHEDULING_PARALLELGROUPNODE_H
