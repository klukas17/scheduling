//
// Created by mihael on 9/3/23.
//

#ifndef SCHEDULING_OPENGROUPPATHTREENODE_H
#define SCHEDULING_OPENGROUPPATHTREENODE_H

#include "GroupPathTreeNode.h"

class OpenGroupPathTreeNode final : public GroupPathTreeNode {
public:
    explicit OpenGroupPathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_OPENGROUPPATHTREENODE_H
