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
    Individual(Topology* topology);
    GenotypeNode* getRootNode();
};


#endif //SCHEDULING_INDIVIDUAL_H
