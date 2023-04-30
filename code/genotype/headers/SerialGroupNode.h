//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_SERIALGROUPNODE_H
#define SCHEDULING_SERIALGROUPNODE_H

#include "GenotypeNode.h"
#include "vector"

class SerialGroupNode : public GenotypeNode {
private:
    std::vector<GenotypeNode*> body;
public:
    explicit SerialGroupNode(long id);
    std::vector<GenotypeNode*> getBody();
    void addNodeToBody(GenotypeNode* node);
};


#endif //SCHEDULING_SERIALGROUPNODE_H
