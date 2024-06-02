//
// Created by mihael on 6/1/24.
//

#ifndef GRAPHBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#define GRAPHBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#include "DoubleGenerator.h"
#include "GBGPNodeTypes.h"
#include "IntegerGenerator.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class GraphBasedGeneticProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    int max_number_of_nodes;
    DoubleGenerator* constant_generator;
    IntegerGenerator* generator;
    std::vector<GBGPNodeType> node_types;
    GraphBasedGeneticProgrammingGenotypeBlueprint(int max_number_of_nodes, double constant_min, double constant_max);
    double generateConstant();
    GBGPNodeType generateNodeType();
};



#endif //GRAPHBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
