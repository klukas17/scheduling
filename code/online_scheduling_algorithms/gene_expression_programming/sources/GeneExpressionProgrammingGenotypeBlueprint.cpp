//
// Created by mihael on 5/29/24.
//

#include "GeneExpressionProgrammingGenotypeBlueprint.h"

#include <climits>

#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

GeneExpressionProgrammingGenotypeBlueprint::GeneExpressionProgrammingGenotypeBlueprint(
    int head_size,
    double tail_chance_of_param,
    double constant_min,
    double constant_max)
{
    this->head_size = head_size;
    this->tail_size = head_size * 2 + 1;
    this->tail_chance_of_param = tail_chance_of_param;
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
    this->node_type_generator = new UniformRealDistributionGenerator(0, 1);
    this->nodes = {
        GEP_CONST,
        GEP_PARAM,
        GEP_UNARY_MINUS,
        GEP_PLUS,
        GEP_MINUS,
        GEP_TIMES,
        GEP_DIVIDE,
        GEP_SQUARE,
        GEP_ROOT,
        GEP_BRANCH
    };
    double segment = 1.0 / nodes.size();
    this->nodes_probabilites.reserve(nodes.size());
    for (int i = 0; i < nodes.size() - 1; i++) {
        nodes_probabilites.push_back(segment * (i + 1));
    }
    nodes_probabilites.push_back(1);
}

double GeneExpressionProgrammingGenotypeBlueprint::generateConstant() {
    return constant_generator->generate();
}

std::string GeneExpressionProgrammingGenotypeBlueprint::generateParam(std::vector<std::string> params) {
    return params[generator->generate() % params.size()];
}

GEPNodeType GeneExpressionProgrammingGenotypeBlueprint::generateNodeTypeForHead() {
    auto random_number = node_type_generator->generate();
    int i = 0;
    while (nodes_probabilites[i] < random_number) {
        i++;
    }
    return nodes[i];
}

GEPNodeType GeneExpressionProgrammingGenotypeBlueprint::generateNodeTypeForTail(){
    auto random_number = node_type_generator->generate();
    if (random_number < tail_chance_of_param) {
        return GEP_PARAM;
    }
    return GEP_CONST;
}
