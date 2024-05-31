//
// Created by mihael on 5/30/24.
//

#ifndef GEPHENOTYPENODE_H
#define GEPHENOTYPENODE_H
#include <map>
#include <string>
#include <vector>

#include "GENodeTypes.h"


class GEPhenotypeNode {
public:
    int node_id;
    GENodeType node_type;
    std::vector<GEPhenotypeNode*> children;
    GEPhenotypeNode(int node_id, GENodeType node_type);
    virtual ~GEPhenotypeNode();
    virtual GEPhenotypeNode* copy();
    virtual double eval(std::map<std::string, double>& params);
    virtual void collectConstants(std::map<int, double>& constants);
};



#endif //GEPHENOTYPENODE_H
