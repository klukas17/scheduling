//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_INDIVIDUAL_H
#define SCHEDULING_INDIVIDUAL_H

#include "Topology.h"
#include "GenotypeNode.h"

class Individual {
private:
    GenotypeNode* root_node;
public:
    explicit Individual(Topology* topology);
    static GenotypeNode* createNode(TopologyElement* topology_element);
    GenotypeNode* getRootNode();
};


#endif //SCHEDULING_INDIVIDUAL_H
