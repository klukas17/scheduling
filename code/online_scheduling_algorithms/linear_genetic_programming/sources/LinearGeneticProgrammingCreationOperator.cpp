//
// Created by mihael on 5/27/24.
//

#include "LinearGeneticProgrammingCreationOperator.h"

#include "LGPInstruction.h"
#include "LGPProgram.h"
#include "LinearGeneticProgramming.h"
#include "UniformRealDistributionGenerator.h"

LinearGeneticProgrammingCreationOperator::LinearGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<LinearGeneticProgrammingGenotypeBlueprint*>(genotype_blueprint);
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
    double segment = (1 - blueprint->initialization_chance_of_nop) / (instructions.size() - 1);
    instructions_probabilites.reserve(instructions.size());
    for (int i = 0; i < instructions.size() - 1; i++) {
        instructions_probabilites.push_back(segment * (i + 1));
    }
    instructions_probabilites.push_back(1);
    this->instruction_type_generator = new UniformRealDistributionGenerator(0, 1);
}

Genotype* LinearGeneticProgrammingCreationOperator::create() {
    std::vector<LGPInstruction*> instructions;
    instructions.reserve(blueprint->number_of_instructions);
    std::map<int, double> load_constant_map;
    std::map<int, std::string> load_param_map;

    for (int i = 0; i < blueprint->number_of_instructions; i++) {
        auto instruction_type = generateInstructionType();
        if (instruction_type == LGP_LOAD_CONSTANT) {
            load_constant_map[i] = blueprint->generateConstant();
        }
        if (instruction_type == LGP_LOAD_PARAM) {
            load_param_map[i] = blueprint->generateParam(blueprint->getInputs());
        }
        instructions.push_back(new LGPInstruction(
            instruction_type,
            blueprint->generateRegister(),
            blueprint->generateRegister(),
            blueprint->generateRegister(),
            i
        ));
    }

    auto program = new LGPProgram(instructions, load_constant_map, load_param_map);
    auto lgp = new LinearGeneticProgramming(program, blueprint->register_initialization_strategy, blueprint->number_of_registers);
    lgp->setInputs(blueprint->getInputs());
    return lgp;
}

LGPInstructionType LinearGeneticProgrammingCreationOperator::generateInstructionType() {
    auto random_number = instruction_type_generator->generate();
    int i = 0;
    while (instructions_probabilites[i] < random_number) {
        i++;
    }
    return instructions[i];
}
