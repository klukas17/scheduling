//
// Created by mihael on 9/3/23.
//

#ifndef SCHEDULING_ROUTEGROUPPATHTREENODE_H
#define SCHEDULING_ROUTEGROUPPATHTREENODE_H

#include "GroupPathTreeNode.h"

class RouteGroupPathTreeNode final : public GroupPathTreeNode {
public:
    explicit RouteGroupPathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_ROUTEGROUPPATHTREENODE_H
