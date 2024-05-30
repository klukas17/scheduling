//
// Created by mihael on 5/29/24.
//

#ifndef GENEEXPRESSIONPROGRAMMINGGENOTYPEBLUEPRINT_H
#define GENEEXPRESSIONPROGRAMMINGGENOTYPEBLUEPRINT_H
#include "DoubleGenerator.h"
#include "GEPNodeTypes.h"
#include "IntegerGenerator.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class GeneExpressionProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    int head_size;
    int tail_size;
    double tail_chance_of_param;
    DoubleGenerator* constant_generator;
    IntegerGenerator* generator;
    DoubleGenerator* node_type_generator;
    std::vector<GEPNodeType> nodes;
    std::vector<double> nodes_probabilites;
    GeneExpressionProgrammingGenotypeBlueprint(
        int head_size,
        double tail_chance_of_param,
        double constant_min,
        double constant_max
    );
    double generateConstant();
    std::string generateParam(std::vector<std::string> params);
    GEPNodeType generateNodeTypeForHead();
    GEPNodeType generateNodeTypeForTail();
};



#endif //GENEEXPRESSIONPROGRAMMINGGENOTYPEBLUEPRINT_H
