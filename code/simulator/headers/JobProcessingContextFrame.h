//
// Created by mihael on 9/14/23.
//

#ifndef SCHEDULING_JOBPROCESSINGCONTEXTFRAME_H
#define SCHEDULING_JOBPROCESSINGCONTEXTFRAME_H

#include "OpenGroupPathTreeNode.h"
#include "map"

class JobProcessingContextFrame {
    OpenGroupPathTreeNode* open_group_path_tree_node;
    std::map<long, bool> children_visited;
public:
    explicit JobProcessingContextFrame(OpenGroupPathTreeNode* open_group_path_tree_node);
    [[nodiscard]] OpenGroupPathTreeNode* getOpenGroupPathTreeNode() const;
    void visitChild(long path_node_id);
    bool checkAllChildrenVisited();
};

#endif //SCHEDULING_JOBPROCESSINGCONTEXTFRAME_H

