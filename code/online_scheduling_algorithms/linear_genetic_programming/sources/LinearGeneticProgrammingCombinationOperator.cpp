//
// Created by mihael on 5/27/24.
//

#include "LinearGeneticProgrammingCombinationOperator.h"

#include <climits>

#include "LinearGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"

LinearGeneticProgrammingCombinationOperator::LinearGeneticProgrammingCombinationOperator(LinearGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

LinearGeneticProgrammingCombinationOperator::~LinearGeneticProgrammingCombinationOperator() {
    delete generator;
}

Genotype* LinearGeneticProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto lgp1 = dynamic_cast<LinearGeneticProgramming*>(genotype1);
    auto lgp2 = dynamic_cast<LinearGeneticProgramming*>(genotype2);

    auto program1 = lgp1->getProgram();
    auto program2 = lgp2->getProgram();

    auto inputs = lgp1->getInputs();

    auto break_point = generator->generate() % (blueprint->number_of_instructions - 1);

    std::vector<LGPInstruction*> instructions;
    instructions.reserve(blueprint->number_of_instructions);
    std::map<int, double> load_constant_map;
    std::map<int, std::string> load_param_map;

    for (int i = 0; i <= break_point; i++) {
        if (program1->load_constant_map.contains(i)) {
            load_constant_map[i] = program1->load_constant_map[i];
        }
        if (program1->load_param_map.contains(i)) {
            load_param_map[i] = program1->load_param_map[i];
        }
        instructions.push_back(program1->instructions[i]->copy());
    }

    for (int i = break_point + 1; i < blueprint->number_of_instructions; i++) {
        if (program2->load_constant_map.contains(i)) {
            load_constant_map[i] = program2->load_constant_map[i];
        }
        if (program2->load_param_map.contains(i)) {
            load_param_map[i] = program2->load_param_map[i];
        }
        instructions.push_back(program2->instructions[i]->copy());
    }

    auto program = new LGPProgram(instructions, load_constant_map, load_param_map);

    auto lgp = new LinearGeneticProgramming(program, blueprint->register_initialization_strategy, blueprint->number_of_registers);
    lgp->setInputs(inputs);
    return lgp;
}
