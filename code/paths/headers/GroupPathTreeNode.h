//
// Created by mihael on 9/3/23.
//

#ifndef SCHEDULING_GROUPPATHTREENODE_H
#define SCHEDULING_GROUPPATHTREENODE_H

#include "PathTreeNode.h"
#include "vector"

class GroupPathTreeNode : public PathTreeNode {
    std::vector<PathTreeNode*> children;
public:
    explicit GroupPathTreeNode(PathNode* path_node);
    ~GroupPathTreeNode() override = 0;
    std::vector<PathTreeNode*> getChildren();
    void addChild(PathTreeNode* path_tree_node);
};

#endif //SCHEDULING_GROUPPATHTREENODE_H
