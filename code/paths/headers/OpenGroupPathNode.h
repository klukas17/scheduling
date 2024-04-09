//
// Created by mihael on 8/20/23.
//

#ifndef SCHEDULING_OPENGROUPPATHNODE_H
#define SCHEDULING_OPENGROUPPATHNODE_H

#include "GroupPathNode.h"
#include "map"

class OpenGroupPathNode final : public GroupPathNode {
    PathNode* next;
    std::map<long, PathNode*> children;
    std::vector<std::pair<long, PathNode*>> sub_path_nodes;
public:
    explicit OpenGroupPathNode(long path_node_id, TopologyElement* topology_element);
    [[nodiscard]] PathNode* getNext() const;
    void setNext(PathNode* path_node);
    [[nodiscard]] std::map<long, PathNode*> getChildren() const;
    void addChild(PathNode* path_node, long path_node_id);
    std::vector<std::pair<long, PathNode*>> getSubPathNodes();
    void addSubPathNode(long id, PathNode* path_node);
};

#endif //SCHEDULING_OPENGROUPPATHNODE_H
