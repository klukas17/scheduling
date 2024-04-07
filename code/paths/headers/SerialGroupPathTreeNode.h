//
// Created by mihael on 9/3/23.
//

#ifndef SCHEDULING_SERIALGROUPPATHTREENODE_H
#define SCHEDULING_SERIALGROUPPATHTREENODE_H

#include "GroupPathTreeNode.h"

class SerialGroupPathTreeNode final : public GroupPathTreeNode {
public:
    explicit SerialGroupPathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_SERIALGROUPPATHTREENODE_H
