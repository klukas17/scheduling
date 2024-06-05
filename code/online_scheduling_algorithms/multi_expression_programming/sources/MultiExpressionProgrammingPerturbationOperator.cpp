//
// Created by mihael on 5/30/24.
//

#include "MultiExpressionProgrammingPerturbationOperator.h"

#include <climits>

#include "MultiExpressionProgramming.h"
#include "UniformIntDistributionGenerator.h"

MultiExpressionProgrammingPerturbationOperator::MultiExpressionProgrammingPerturbationOperator(MultiExpressionProgrammingGenotypeBlueprint* blueprint, double perturbation_rate) {
    this->blueprint = blueprint;
    this->perturbation_rate = perturbation_rate;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

MultiExpressionProgrammingPerturbationOperator::~MultiExpressionProgrammingPerturbationOperator() {
    delete generator;
}

void MultiExpressionProgrammingPerturbationOperator::perturbate(Genotype* genotype) {
    auto mep = dynamic_cast<MultiExpressionProgramming*>(genotype);
    auto program = mep->getProgram();
    auto changes = blueprint->number_of_instructions * perturbation_rate;

    for (int i = 0; i < changes; i++) {
        auto instruction_index = generator->generate() % blueprint->number_of_instructions;
        auto instruction = program->instructions[instruction_index];

        if (instruction->instruction_type == MEP_CONSTANT) {
            program->constant_map.erase(instruction_index);
        }
        if (instruction->instruction_type == MEP_PARAM) {
            program->param_map.erase(instruction_index);
        }

        switch(instruction->instruction_id) {

        case 0:
            {
                instruction->instruction_type = blueprint->generateNullaryFunction();
                break;
            }

        case 1:
            {
                auto random_number = generator->generate() % 2;
                if (random_number == 0) {
                    instruction->instruction_type = blueprint->generateUnaryFunction();
                } else if (random_number == 1) {
                    instruction->first_param = blueprint->generateArgument(instruction->instruction_id);
                }
                break;
            }

        case 2:
            {
                auto random_number = generator->generate() % 3;
                if (random_number == 0) {
                    instruction->instruction_type = blueprint->generateBinaryFunction();
                } else if (random_number == 1) {
                    instruction->first_param = blueprint->generateArgument(instruction->instruction_id);
                }else if (random_number == 2) {
                    instruction->second_param = blueprint->generateArgument(instruction->instruction_id);
                }
                break;
            }

        default:
            {
                auto random_number = generator->generate() % 4;
                if (random_number == 0) {
                    instruction->instruction_type = blueprint->generateTernaryFunction();
                } else if (random_number == 1) {
                    instruction->first_param = blueprint->generateArgument(instruction->instruction_id);
                } else if (random_number == 2) {
                    instruction->second_param = blueprint->generateArgument(instruction->instruction_id);
                } else if (random_number == 3) {
                    instruction->third_param = blueprint->generateArgument(instruction->instruction_id);
                }
                break;
            }
        }

        if (instruction->instruction_type == MEP_CONSTANT) {
            program->constant_map[i] = blueprint->generateConstant();
        }
        if (instruction->instruction_type == MEP_PARAM) {
            program->param_map[i] = blueprint->generateParam(mep->getInputs());
        }
    }
}
