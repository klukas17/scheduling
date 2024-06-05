//
// Created by mihael on 5/27/24.
//

#include "LinearGeneticProgrammingPerturbationOperator.h"

#include <climits>

#include "LinearGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

LinearGeneticProgrammingPerturbationOperator::LinearGeneticProgrammingPerturbationOperator(
    LinearGeneticProgrammingGenotypeBlueprint* blueprint,
    double perturbation_rate,
    double perturbation_chance_of_nop
) {
    this->blueprint = blueprint;
    instructions = {
        LGP_LOAD_PARAM,
        LGP_LOAD_CONSTANT,
        LGP_UNARY_MINUS,
        LGP_PLUS,
        LGP_MINUS,
        LGP_TIMES,
        LGP_DIVIDE,
        LGP_SQUARE,
        LGP_ROOT,
        LGP_CONDITION,
        LGP_NOP
    };
    instructions_probabilites.reserve(instructions.size());
    double segment = (1 - perturbation_chance_of_nop) / (instructions.size() - 1);
    for (int i = 0; i < instructions.size() - 1; i++) {
        instructions_probabilites.push_back(segment * (i + 1));
    }
    instructions_probabilites.push_back(1);
    this->instruction_type_generator = new UniformRealDistributionGenerator(0, 1);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
    this->perturbation_rate = perturbation_rate;
}

LinearGeneticProgrammingPerturbationOperator::~LinearGeneticProgrammingPerturbationOperator() {
    delete instruction_type_generator;
    delete generator;
}

void LinearGeneticProgrammingPerturbationOperator::perturbate(Genotype* genotype) {
    auto lgp = dynamic_cast<LinearGeneticProgramming*>(genotype);
    auto program = lgp->getProgram();
    auto changes = blueprint->number_of_instructions * perturbation_rate;

    for (int i = 0; i < changes; i++) {
        auto instruction_index = generator->generate() % blueprint->number_of_instructions;
        auto instruction = program->instructions[instruction_index];
        auto index_to_change = generator->generate() % 4;
        if (index_to_change == 0) {
            if (instruction->instruction_type == LGP_LOAD_CONSTANT) {
                program->load_constant_map.erase(instruction_index);
            }
            if (instruction->instruction_type == LGP_LOAD_PARAM) {
                program->load_param_map.erase(instruction_index);
            }
            auto instruction_type = generateInstructionType();
            instruction->instruction_type = instruction_type;
            if (instruction_type == LGP_LOAD_CONSTANT) {
                program->load_constant_map[instruction_index] = blueprint->generateConstant();
            }
            if (instruction_type == LGP_LOAD_PARAM) {
                program->load_param_map[instruction_index] = blueprint->generateParam(lgp->getInputs());
            }
        } else if (index_to_change == 1) {
            instruction->first_register_id = blueprint->generateRegister();
        } else if (index_to_change == 2) {
            instruction->second_register_id = blueprint->generateRegister();
        } else if (index_to_change == 3) {
            instruction->third_register_id = blueprint->generateRegister();
        }
    }
}

LGPInstructionType LinearGeneticProgrammingPerturbationOperator::generateInstructionType() {
    auto random_number = instruction_type_generator->generate();
    int i = 0;
    while (instructions_probabilites[i] < random_number) {
        i++;
    }
    return instructions[i];
}
