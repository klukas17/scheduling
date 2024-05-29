//
// Created by mihael on 5/29/24.
//

#include "StackBasedGeneticProgrammingCreationOperator.h"

#include <map>

#include "SBGPInstruction.h"
#include "SBGPProgram.h"
#include "StackBasedGeneticProgramming.h"
#include "UniformRealDistributionGenerator.h"

StackBasedGeneticProgrammingCreationOperator::StackBasedGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<StackBasedGeneticProgrammingGenotypeBlueprint*>(genotype_blueprint);
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
        SBGP_CONDITION,
        SBGP_NOP
    };
    double segment = (1 - blueprint->initialization_chance_of_nop) * (1 - blueprint->push_param_share - blueprint->push_constant_share) / (instructions.size() - 3);
    instructions_probabilites.reserve(instructions.size());
    instructions_probabilites.push_back((1 - blueprint->initialization_chance_of_nop) * blueprint->push_param_share);
    instructions_probabilites.push_back((1 - blueprint->initialization_chance_of_nop) * (blueprint->push_param_share + blueprint->push_constant_share));
    double offset = instructions_probabilites[1];
    for (int i = 0; i < instructions.size() - 3; i++) {
        instructions_probabilites.push_back(offset + segment * (i + 1));
    }
    instructions_probabilites.push_back(1);
    this->instruction_type_generator = new UniformRealDistributionGenerator(0, 1);
}

Genotype* StackBasedGeneticProgrammingCreationOperator::create() {
    std::vector<SBGPInstruction*> instructions;
    instructions.reserve(blueprint->number_of_instructions);
    std::map<int, double> push_constant_map;
    std::map<int, std::string> push_param_map;

    for (int i = 0; i < blueprint->number_of_instructions; i++) {
        auto instruction_type = generateInstructionType();
        if (instruction_type == SBGP_PUSH_CONSTANT) {
            push_constant_map[i] = blueprint->generateConstant();
        }
        if (instruction_type == SBGP_PUSH_PARAM) {
            push_param_map[i] = blueprint->generateParam(blueprint->getInputs());
        }
        instructions.push_back(new SBGPInstruction(
            instruction_type,
            i
        ));
    }

    auto program = new SBGPProgram(instructions, push_constant_map, push_param_map);
    auto sbgp = new StackBasedGeneticProgramming(program);
    sbgp->setInputs(blueprint->getInputs());
    return sbgp;
}

SBGPInstructionType StackBasedGeneticProgrammingCreationOperator::generateInstructionType() {
    auto random_number = instruction_type_generator->generate();
    int i = 0;
    while (instructions_probabilites[i] < random_number) {
        i++;
    }
    return instructions[i];
}
