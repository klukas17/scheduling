//
// Created by mihael on 01/05/23.
//

#ifndef SCHEDULING_PARALLELGROUPNODE_H
#define SCHEDULING_PARALLELGROUPNODE_H

#include "GenotypeNode.h"
#include "vector"

class ParallelGroupNode : public GenotypeNode {
private:
    std::vector<GenotypeNode*> body;
public:
    explicit ParallelGroupNode(long id);
    std::vector<GenotypeNode*> getBody();
    void addNodeToBody(GenotypeNode* node);
};


#endif //SCHEDULING_PARALLELGROUPNODE_H
