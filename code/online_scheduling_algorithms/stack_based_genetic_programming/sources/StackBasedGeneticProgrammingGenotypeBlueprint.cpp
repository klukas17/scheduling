//
// Created by mihael on 5/29/24.
//

#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"

#include <climits>

#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

StackBasedGeneticProgrammingGenotypeBlueprint::StackBasedGeneticProgrammingGenotypeBlueprint(
    int number_of_instructions,
    double initialization_chance_of_nop,
    double push_constant_share,
    double push_param_share,
    double constant_min,
    double constant_max
) {
    this->number_of_instructions = number_of_instructions;
    this->initialization_chance_of_nop = initialization_chance_of_nop;
    this->push_constant_share = push_constant_share;
    this->push_param_share = push_param_share;
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

StackBasedGeneticProgrammingGenotypeBlueprint::~StackBasedGeneticProgrammingGenotypeBlueprint() {
    delete constant_generator;
    delete generator;
}

double StackBasedGeneticProgrammingGenotypeBlueprint::generateConstant() {
    return constant_generator->generate();
}

std::string StackBasedGeneticProgrammingGenotypeBlueprint::generateParam(std::vector<std::string> params) {
    return params[generator->generate() % params.size()];
}
