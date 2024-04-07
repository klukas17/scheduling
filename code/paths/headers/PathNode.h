//
// Created by mihael on 29/06/23.
//

#ifndef SCHEDULING_PATHNODE_H
#define SCHEDULING_PATHNODE_H

#include "vector"
#include "TopologyElement.h"
#include "Prerequisite.h"

class PathNode {
protected:
    long path_node_id;
    TopologyElement* topology_element;
    std::vector<Prerequisite*> prerequisites;
public:
    PathNode(long path_node_id, TopologyElement* topology_element);
    virtual ~PathNode() = 0;
    [[nodiscard]] long getPathNodeId() const;
    [[nodiscard]] TopologyElement* getTopologyElement() const;
    std::vector<Prerequisite*> getPrerequisites();
    void addPrerequisite(Prerequisite* prerequisite);
    void deletePathNode();
    static void findSubPathNodes(PathNode* current_node, std::set<PathNode*>& sub_path_nodes);
};

#endif //SCHEDULING_PATHNODE_H
