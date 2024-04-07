//
// Created by mihael on 9/3/23.
//

#ifndef SCHEDULING_PATHTREENODE_H
#define SCHEDULING_PATHTREENODE_H

#include "PathNode.h"

class PathTreeNode {
    PathNode* path_node;
public:
    explicit PathTreeNode(PathNode* path_node);
    virtual ~PathTreeNode() = 0;
    [[nodiscard]] PathNode* getPathNode() const;
    void deletePathTreeNode();
};

#endif //SCHEDULING_PATHTREENODE_H
