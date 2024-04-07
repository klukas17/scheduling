//
// Created by mihael on 8/20/23.
//

#ifndef SCHEDULING_PARALLELGROUPPATHNODE_H
#define SCHEDULING_PARALLELGROUPPATHNODE_H

#include "GroupPathNode.h"
#include "map"

class ParallelGroupPathNode final : public GroupPathNode {
    std::map<long, PathNode*> next;
public:
    explicit ParallelGroupPathNode(long path_node_id, TopologyElement* topology_element);
    std::map<long, PathNode*> getNext();
    void setNext(long id, PathNode* path_node);
};

#endif //SCHEDULING_PARALLELGROUPPATHNODE_H
