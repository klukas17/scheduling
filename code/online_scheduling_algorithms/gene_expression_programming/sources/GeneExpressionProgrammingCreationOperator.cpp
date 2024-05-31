//
// Created by mihael on 5/29/24.
//

#include "GeneExpressionProgrammingCreationOperator.h"

#include "GeneExpressionProgramming.h"
#include "GEPProgram.h"

GeneExpressionProgrammingCreationOperator::GeneExpressionProgrammingCreationOperator(GenotypeBlueprint* blueprint) : CreationOperator(blueprint) {
    this->blueprint = dynamic_cast<GeneExpressionProgrammingGenotypeBlueprint*>(blueprint);
}

Genotype* GeneExpressionProgrammingCreationOperator::create() {

    std::vector<GEPGenotypeNode*> genotype_nodes;
    std::map<int, double> constant_map;
    std::map<int, std::string> param_map;

    for (int i = 0; i < blueprint->head_size + blueprint->tail_size; i++) {
        auto node_type = i < blueprint->head_size ? blueprint->generateNodeTypeForHead() : blueprint->generateNodeTypeForTail();
        if (node_type == GEP_CONST) {
            constant_map[i] = blueprint->generateConstant();
        }
        if (node_type == GEP_PARAM) {
            param_map[i] = blueprint->generateParam(blueprint->getInputs());
        }
        genotype_nodes.push_back(new GEPGenotypeNode(i, node_type));
    }

    auto program = new GEPProgram(genotype_nodes, constant_map, param_map);
    auto gep = new GeneExpressionProgramming(program);
    gep->setInputs(blueprint->getInputs());
    return gep;
}
