//
// Created by mihael on 8/20/23.
//

#ifndef SCHEDULING_MACHINEPATHNODE_H
#define SCHEDULING_MACHINEPATHNODE_H

#include "PathNode.h"

class MachinePathNode final : public PathNode {
    PathNode* next;
public:
    explicit MachinePathNode(long path_node_id, TopologyElement* topology_element);
    [[nodiscard]] PathNode* getNext() const;
    void setNext(PathNode* path_node);
};

#endif //SCHEDULING_MACHINEPATHNODE_H
