//
// Created by mihael on 29/06/23.
//

#ifndef SCHEDULING_PATHNODE_H
#define SCHEDULING_PATHNODE_H

#include "vector"
#include "map"
#include "TopologyElement.h"
#include "Prerequisite.h"

class PathNode {
private:
    TopologyElement* topology_element;
    std::vector<Prerequisite*> prerequisites;
    std::map<long, PathNode*> children;
public:
    explicit PathNode(TopologyElement* topology_element);
    TopologyElement* getTopologyElement();
    std::vector<Prerequisite*> getPrerequisites();
    void addPrerequisite(Prerequisite* prerequisite);
    std::map<long, PathNode*> getChildren();
    void addChild(PathNode* child);
};


#endif //SCHEDULING_PATHNODE_H
