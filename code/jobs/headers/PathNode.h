//
// Created by mihael on 29/06/23.
//

#ifndef SCHEDULING_PATHNODE_H
#define SCHEDULING_PATHNODE_H

#include "vector"
#include "Prerequisite.h"

class PathNode {
private:
    long machine_id;
    std::vector<Prerequisite*> prerequisites;
    std::vector<PathNode*> children;
public:
    PathNode(long machine_id);
    long getMachineId();
    std::vector<Prerequisite*> getPrerequisites();
    void addPrerequisite(Prerequisite* prerequisite);
    std::vector<PathNode*> getChildren();
    void addChild(PathNode* child);
};


#endif //SCHEDULING_PATHNODE_H
