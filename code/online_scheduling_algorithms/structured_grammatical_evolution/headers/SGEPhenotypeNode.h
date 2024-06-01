//
// Created by mihael on 5/31/24.
//

#ifndef SGEPHENOTYPENODE_H
#define SGEPHENOTYPENODE_H
#include <map>
#include <string>
#include <vector>

#include "SGENodeTypes.h"


class SGEPhenotypeNode {
public:
    int node_id;
    int depth;
    SGENodeType node_type;
    std::vector<SGEPhenotypeNode*> children;
    SGEPhenotypeNode(int node_id, int depth, SGENodeType node_type);
    virtual ~SGEPhenotypeNode();
    virtual SGEPhenotypeNode* copy();
    virtual double eval(std::map<std::string, double>& params);
    virtual void collectConstants(std::map<int, double>& constants);
};



#endif //SGEPHENOTYPENODE_H
