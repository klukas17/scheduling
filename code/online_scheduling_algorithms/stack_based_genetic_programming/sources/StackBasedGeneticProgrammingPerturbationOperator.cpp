//
// Created by mihael on 5/29/24.
//

#include "StackBasedGeneticProgrammingPerturbationOperator.h"

#include <climits>

#include "StackBasedGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

StackBasedGeneticProgrammingPerturbationOperator::StackBasedGeneticProgrammingPerturbationOperator(
    StackBasedGeneticProgrammingGenotypeBlueprint* blueprint,
    double perturbation_rate,
    double perturbation_chance_of_nop
) {
    this->blueprint = blueprint;
    instructions = {
        SBGP_PUSH_PARAM,
        SBGP_PUSH_CONSTANT,
        SBGP_UNARY_MINUS,
        SBGP_PLUS,
        SBGP_MINUS,
        SBGP_TIMES,
        SBGP_DIVIDE,
        SBGP_SQUARE,
        SBGP_ROOT,
        SBGP_BRANCH,
        SBGP_NOP
    };
    double segment = (1 - perturbation_chance_of_nop) * (1 - blueprint->push_param_share - blueprint->push_constant_share) / (instructions.size() - 3);
    instructions_probabilites.reserve(instructions.size());
    instructions_probabilites.push_back((1 - perturbation_chance_of_nop) * blueprint->push_param_share);
    instructions_probabilites.push_back((1 - perturbation_chance_of_nop) * (blueprint->push_param_share + blueprint->push_constant_share));
    double offset = instructions_probabilites[1];
    for (int i = 0; i < instructions.size() - 3; i++) {
        instructions_probabilites.push_back(offset + segment * (i + 1));
    }
    instructions_probabilites.push_back(1);
    this->instruction_type_generator = new UniformRealDistributionGenerator(0, 1);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
    this->perturbation_rate = perturbation_rate;
}

StackBasedGeneticProgrammingPerturbationOperator::~StackBasedGeneticProgrammingPerturbationOperator() {
    delete instruction_type_generator;
    delete generator;
}

void StackBasedGeneticProgrammingPerturbationOperator::perturbate(Genotype* genotype) {
    auto sbgp = dynamic_cast<StackBasedGeneticProgramming*>(genotype);
    auto program = sbgp->getProgram();
    auto changes = blueprint->number_of_instructions * perturbation_rate;

    for (int i = 0; i < changes; i++) {
        auto instruction_index = generator->generate() % blueprint->number_of_instructions;
        auto instruction = program->instructions[instruction_index];

        if (instruction->instruction_type == SBGP_PUSH_CONSTANT) {
            program->push_constant_map.erase(instruction_index);
        }
        if (instruction->instruction_type == SBGP_PUSH_PARAM) {
            program->push_param_map.erase(instruction_index);
        }

        auto instruction_type = generateInstructionType();
        instruction->instruction_type = instruction_type;

        if (instruction_type == SBGP_PUSH_CONSTANT) {
            program->push_constant_map[instruction_index] = blueprint->generateConstant();
        }
        if (instruction_type == SBGP_PUSH_PARAM) {
            program->push_param_map[instruction_index] = blueprint->generateParam(sbgp->getInputs());
        }
    }
}

SBGPInstructionType StackBasedGeneticProgrammingPerturbationOperator::generateInstructionType() {
    auto random_number = instruction_type_generator->generate();
    int i = 0;
    while (instructions_probabilites[i] < random_number) {
        i++;
    }
    return instructions[i];
}
