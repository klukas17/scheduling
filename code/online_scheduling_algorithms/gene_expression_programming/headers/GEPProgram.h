//
// Created by mihael on 5/30/24.
//

#ifndef GEPPROGRAM_H
#define GEPPROGRAM_H

#include <map>
#include <string>
#include <vector>
#include "GEPGenotypeNode.h"
#include "GEPPhenotypeNode.h"


class GEPProgram {
public:
    std::vector<GEPGenotypeNode*> genotype_nodes; // head and tail concatenated
    GEPPhenotypeNode* phenotype_root_node;
    std::map<int, double> constant_map;
    std::map<int, std::string> param_map;
    GEPProgram(
    std::vector<GEPGenotypeNode*> genotype_nodes,
        std::map<int, double> constant_map,
        std::map<int, std::string> param_map
    );
    ~GEPProgram();
    GEPProgram* copy();
    void buildPhenotype();
    double executeProgram(std::map<std::string, double> params);
};



#endif //GEPPROGRAM_H
