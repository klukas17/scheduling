//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPENODE_H
#define SCHEDULING_GENOTYPENODE_H

#include "NodeType.h"

class GenotypeNode {
protected:
    NodeType node_type;
public:
    GenotypeNode();
    virtual ~GenotypeNode() = 0;
};


#endif //SCHEDULING_GENOTYPENODE_H
