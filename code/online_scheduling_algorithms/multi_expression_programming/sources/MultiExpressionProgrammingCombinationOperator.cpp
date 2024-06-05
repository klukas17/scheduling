//
// Created by mihael on 5/30/24.
//

#include "MultiExpressionProgrammingCombinationOperator.h"

#include <climits>

#include "MultiExpressionProgramming.h"
#include "UniformIntDistributionGenerator.h"

MultiExpressionProgrammingCombinationOperator::MultiExpressionProgrammingCombinationOperator(MultiExpressionProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

MultiExpressionProgrammingCombinationOperator::~MultiExpressionProgrammingCombinationOperator() {
    delete generator;
}

Genotype* MultiExpressionProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto mep1 = dynamic_cast<MultiExpressionProgramming*>(genotype1);
    auto mep2 = dynamic_cast<MultiExpressionProgramming*>(genotype2);

    auto program1 = mep1->getProgram();
    auto program2 = mep2->getProgram();

    auto inputs = mep1->getInputs();

    auto break_point = generator->generate() % (blueprint->number_of_instructions - 1);

    std::vector<MEPInstruction*> instructions;
    instructions.reserve(blueprint->number_of_instructions);
    std::map<int, double> constant_map;
    std::map<int, std::string> param_map;

    for (int i = 0; i <= break_point; i++) {
        if (program1->constant_map.contains(i)) {
            constant_map[i] = program1->constant_map[i];
        }
        if (program1->param_map.contains(i)) {
            param_map[i] = program1->param_map[i];
        }
        instructions.push_back(program1->instructions[i]->copy());
    }

    for (int i = break_point + 1; i < blueprint->number_of_instructions; i++) {
        if (program2->constant_map.contains(i)) {
            constant_map[i] = program2->constant_map[i];
        }
        if (program2->param_map.contains(i)) {
            param_map[i] = program2->param_map[i];
        }
        instructions.push_back(program2->instructions[i]->copy());
    }

    auto program = new MEPProgram(instructions, constant_map, param_map);

    auto mep = new MultiExpressionProgramming(program);
    mep->setInputs(inputs);
    return mep;
}
