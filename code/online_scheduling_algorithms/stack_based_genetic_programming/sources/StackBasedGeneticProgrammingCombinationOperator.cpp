//
// Created by mihael on 5/29/24.
//

#include "StackBasedGeneticProgrammingCombinationOperator.h"

#include <climits>

#include "StackBasedGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"

StackBasedGeneticProgrammingCombinationOperator::StackBasedGeneticProgrammingCombinationOperator(StackBasedGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

Genotype* StackBasedGeneticProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto sbgp1 = dynamic_cast<StackBasedGeneticProgramming*>(genotype1);
    auto sbgp2 = dynamic_cast<StackBasedGeneticProgramming*>(genotype2);

    auto program1 = sbgp1->getProgram();
    auto program2 = sbgp2->getProgram();

    auto inputs = sbgp1->getInputs();

    auto break_point = generator->generate() % (blueprint->number_of_instructions - 1);

    std::vector<SBGPInstruction*> instructions;
    instructions.reserve(blueprint->number_of_instructions);
    std::map<int, double> push_constant_map;
    std::map<int, std::string> push_param_map;

    for (int i = 0; i <= break_point; i++) {
        if (program1->push_constant_map.contains(i)) {
            push_constant_map[i] = program1->push_constant_map[i];
        }
        if (program1->push_param_map.contains(i)) {
            push_param_map[i] = program1->push_param_map[i];
        }
        instructions.push_back(program1->instructions[i]->copy());
    }

    for (int i = break_point + 1; i < blueprint->number_of_instructions; i++) {
        if (program2->push_constant_map.contains(i)) {
            push_constant_map[i] = program2->push_constant_map[i];
        }
        if (program2->push_param_map.contains(i)) {
            push_param_map[i] = program2->push_param_map[i];
        }
        instructions.push_back(program2->instructions[i]->copy());
    }

    auto program = new SBGPProgram(instructions, push_constant_map, push_param_map);

    auto sbgp = new StackBasedGeneticProgramming(program);
    sbgp->setInputs(inputs);
    return sbgp;
}
