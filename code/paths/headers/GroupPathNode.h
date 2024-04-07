//
// Created by mihael on 8/20/23.
//

#ifndef SCHEDULING_GROUPPATHNODE_H
#define SCHEDULING_GROUPPATHNODE_H

#include "PathNode.h"

class GroupPathNode : public PathNode {
public:
    explicit GroupPathNode(long path_node_id, TopologyElement* topology_element);
    ~GroupPathNode() override = 0;
};

#endif //SCHEDULING_GROUPPATHNODE_H
