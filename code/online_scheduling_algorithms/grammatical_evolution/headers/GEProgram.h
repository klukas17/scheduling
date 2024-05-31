//
// Created by mihael on 5/30/24.
//

#ifndef GEPROGRAM_H
#define GEPROGRAM_H
#include <map>
#include <string>
#include <vector>

#include "GEGenotypeNode.h"
#include "GEPhenotypeNode.h"


class GEProgram {
public:
    std::vector<GEGenotypeNode*> genotype_nodes;
    GEPhenotypeNode* phenotype_root_node;
    explicit GEProgram(std::vector<GEGenotypeNode*> genotype_nodes);
    GEProgram(std::vector<GEGenotypeNode*> genotype_nodes, GEPhenotypeNode* phenotype_root_node);
    ~GEProgram();
    GEProgram* copy();
    std::map<int, double> collectAllConstants();
    double executeProgram(std::map<std::string, double> params);
};



#endif //GEPROGRAM_H
