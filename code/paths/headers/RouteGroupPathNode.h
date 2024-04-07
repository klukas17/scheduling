//
// Created by mihael on 8/20/23.
//

#ifndef SCHEDULING_ROUTEGROUPPATHNODE_H
#define SCHEDULING_ROUTEGROUPPATHNODE_H

#include "GroupPathNode.h"

class RouteGroupPathNode final : public GroupPathNode {
    PathNode* next;
public:
    explicit RouteGroupPathNode(long path_node_id, TopologyElement* topology_element);
    [[nodiscard]] PathNode* getNext() const;
    void setNext(PathNode* path_node);
};

#endif //SCHEDULING_ROUTEGROUPPATHNODE_H
