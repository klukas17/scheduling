//
// Created by mihael on 5/29/24.
//

#include "GeneExpressionProgrammingCombinationOperator.h"

#include <climits>

#include "GeneExpressionProgramming.h"
#include "UniformIntDistributionGenerator.h"

GeneExpressionProgrammingCombinationOperator::GeneExpressionProgrammingCombinationOperator(GeneExpressionProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

Genotype* GeneExpressionProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto gep1 = dynamic_cast<GeneExpressionProgramming*>(genotype1);
    auto gep2 = dynamic_cast<GeneExpressionProgramming*>(genotype2);

    auto program1 = gep1->getProgram();
    auto program2 = gep2->getProgram();

    auto inputs = gep1->getInputs();

    auto break_point = generator->generate() % (blueprint->head_size + blueprint->tail_size - 1);

    std::vector<GEPGenotypeNode*> nodes;
    nodes.reserve(blueprint->head_size + blueprint->tail_size);
    std::map<int, double> constant_map;
    std::map<int, std::string> param_map;

    for (int i = 0; i <= break_point; i++) {
        if (program1->constant_map.contains(i)) {
            constant_map[i] = program1->constant_map[i];
        }
        if (program1->param_map.contains(i)) {
            param_map[i] = program1->param_map[i];
        }
        nodes.push_back(program1->genotype_nodes[i]->copy());
    }

    for (int i = break_point + 1; i < blueprint->head_size + blueprint->tail_size; i++) {
        if (program2->constant_map.contains(i)) {
            constant_map[i] = program2->constant_map[i];
        }
        if (program2->param_map.contains(i)) {
            param_map[i] = program2->param_map[i];
        }
        nodes.push_back(program2->genotype_nodes[i]->copy());
    }

    auto program = new GEPProgram(nodes, constant_map, param_map);

    auto gep = new GeneExpressionProgramming(program);
    gep->setInputs(inputs);
    return gep;
}
