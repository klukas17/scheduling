//
// Created by mihael on 5/29/24.
//

#ifndef GEPPHENOTYPENODE_H
#define GEPPHENOTYPENODE_H
#include <map>
#include <string>
#include <vector>

#include "GEPNodeTypes.h"


class GEPPhenotypeNode {
public:
    int node_id;
    GEPNodeType node_type;
    std::map<int, double> constant_map;
    std::map<int, std::string> param_map;
    std::vector<GEPPhenotypeNode*> children;
    GEPPhenotypeNode(int node_id, GEPNodeType node_type, std::map<int, double> constant_map, std::map<int, std::string> param_map);
    ~GEPPhenotypeNode();
    GEPPhenotypeNode* copy();
    double eval(std::map<std::string, double>& params);
};



#endif //GEPPHENOTYPENODE_H
