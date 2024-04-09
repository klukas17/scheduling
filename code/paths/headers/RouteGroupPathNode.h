//
// Created by mihael on 8/20/23.
//

#ifndef SCHEDULING_ROUTEGROUPPATHNODE_H
#define SCHEDULING_ROUTEGROUPPATHNODE_H

#include "GroupPathNode.h"
#include "map"

class RouteGroupPathNode final : public GroupPathNode {
    PathNode* next;
    std::map<long, PathNode*> children;
public:
    explicit RouteGroupPathNode(long path_node_id, TopologyElement* topology_element);
    [[nodiscard]] PathNode* getNext() const;
    void setNext(PathNode* path_node);
    [[nodiscard]] std::map<long, PathNode*> getChildren() const;
    void addChild(PathNode* path_node, long path_node_id);
};

#endif //SCHEDULING_ROUTEGROUPPATHNODE_H
