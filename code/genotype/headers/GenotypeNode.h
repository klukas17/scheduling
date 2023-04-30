//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPENODE_H
#define SCHEDULING_GENOTYPENODE_H

#include "NodeType.h"

class GenotypeNode {
protected:
    long id;
    NodeType node_type;
public:
    explicit GenotypeNode(long id);
    virtual ~GenotypeNode() = 0;
    [[nodiscard]] long getId() const;
    NodeType getNodeType();
};


#endif //SCHEDULING_GENOTYPENODE_H
