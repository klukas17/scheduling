//
// Created by mihael on 8/20/23.
//

#ifndef SCHEDULING_SERIALGROUPPATHNODE_H
#define SCHEDULING_SERIALGROUPPATHNODE_H

#include "GroupPathNode.h"

class SerialGroupPathNode final : public GroupPathNode {
    PathNode* next;
public:
    explicit SerialGroupPathNode(long path_node_id, TopologyElement* topology_element);
    [[nodiscard]] PathNode* getNext() const;
    void setNext(PathNode* path_node);
};

#endif //SCHEDULING_SERIALGROUPPATHNODE_H
