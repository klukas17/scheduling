//
// Created by mihael on 01/05/23.
//

#ifndef SCHEDULING_GROUPNODE_H
#define SCHEDULING_GROUPNODE_H

#include "GenotypeNode.h"
#include "vector"

class GroupNode : public GenotypeNode {
protected:
    std::vector<GenotypeNode*> body;
public:
    explicit GroupNode(long id);
    ~GroupNode() override = 0;
    std::vector<GenotypeNode*> getBody();
    void addNodeToBody(GenotypeNode* node);
};

#endif //SCHEDULING_GROUPNODE_H
