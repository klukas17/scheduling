//
// Created by mihael on 5/29/24.
//

#ifndef GEPGENOTYPENODE_H
#define GEPGENOTYPENODE_H
#include "GEPNodeTypes.h"


class GEPGenotypeNode {
public:
    int node_id;
    GEPNodeType node_type;
    GEPGenotypeNode(int node_id, GEPNodeType node_type);
    ~GEPGenotypeNode();
    GEPGenotypeNode* copy();
};



#endif //GEPGENOTYPENODE_H
