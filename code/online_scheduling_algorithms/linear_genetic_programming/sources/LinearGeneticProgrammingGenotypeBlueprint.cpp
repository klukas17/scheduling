//
// Created by mihael on 5/27/24.
//

#include "LinearGeneticProgrammingGenotypeBlueprint.h"

#include <climits>

#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

LinearGeneticProgrammingGenotypeBlueprint::LinearGeneticProgrammingGenotypeBlueprint(
    LGPRegisterInitializationStrategy* register_initialization_strategy,
    int number_of_registers,
    int number_of_instructions,
    double initialization_chance_of_nop,
    double constant_min,
    double constant_max
) {
    this->register_initialization_strategy = register_initialization_strategy;
    this->number_of_registers = number_of_registers;
    this->number_of_instructions = number_of_instructions;
    this->initialization_chance_of_nop = initialization_chance_of_nop;
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

double LinearGeneticProgrammingGenotypeBlueprint::generateConstant() {
    return constant_generator->generate();
}

std::string LinearGeneticProgrammingGenotypeBlueprint::generateParam(std::vector<std::string> params) {
    return params[generator->generate() % params.size()];
}

int LinearGeneticProgrammingGenotypeBlueprint::generateRegister() {
    return generator->generate() % number_of_registers;
}
