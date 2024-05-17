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
    std::vector<PathNode*> predecessors;
    double remaining_processing_time;
public:
    PathNode(long path_node_id, TopologyElement* topology_element);
    virtual ~PathNode() = 0;
    [[nodiscard]] long getPathNodeId() const;
    [[nodiscard]] TopologyElement* getTopologyElement() const;
    std::vector<Prerequisite*> getPrerequisites();
    void addPrerequisite(Prerequisite* prerequisite);
    std::vector<PathNode*> getPredecessors();
    void addPredecessor(PathNode* predecessor);
    double getRemainingProcessingTime();
    void setRemainingProcessingTime(double remaining_processing_time);
    void deletePathNode();
    static void findSubPathNodes(PathNode* current_node, std::set<PathNode*>& sub_path_nodes);
};

#endif //SCHEDULING_PATHNODE_H
