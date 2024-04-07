//
// Created by mihael on 9/3/23.
//

#ifndef SCHEDULING_PARALLELGROUPPATHTREENODE_H
#define SCHEDULING_PARALLELGROUPPATHTREENODE_H

#include "GroupPathTreeNode.h"

class ParallelGroupPathTreeNode final: public GroupPathTreeNode {
public:
    explicit ParallelGroupPathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_PARALLELGROUPPATHTREENODE_H
