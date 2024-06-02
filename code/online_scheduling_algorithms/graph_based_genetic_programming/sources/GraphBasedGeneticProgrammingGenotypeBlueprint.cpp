//
// Created by mihael on 6/1/24.
//

#include "GraphBasedGeneticProgrammingGenotypeBlueprint.h"

#include <limits.h>

#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

GraphBasedGeneticProgrammingGenotypeBlueprint::GraphBasedGeneticProgrammingGenotypeBlueprint(int max_number_of_nodes, double constant_min, double constant_max) {
    this->max_number_of_nodes = max_number_of_nodes;
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
    this->node_types = {
        GBGP_CONST,
        GBGP_UNARY_MINUS,
        GBGP_PLUS,
        GBGP_MINUS,
        GBGP_TIMES,
        GBGP_DIVIDE,
        GBGP_SQUARE,
        GBGP_ROOT,
        GBGP_BRANCH
    };
}

double GraphBasedGeneticProgrammingGenotypeBlueprint::generateConstant() {
    return constant_generator->generate();
}

GBGPNodeType GraphBasedGeneticProgrammingGenotypeBlueprint::generateNodeType() {
    return node_types[generator->generate() % node_types.size()];
}
