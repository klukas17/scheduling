//
// Created by mihael on 9/3/23.
//

#ifndef SCHEDULING_MACHINEPATHTREENODE_H
#define SCHEDULING_MACHINEPATHTREENODE_H

#include "PathTreeNode.h"

class MachinePathTreeNode final : public PathTreeNode {
public:
    explicit MachinePathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_MACHINEPATHTREENODE_H
