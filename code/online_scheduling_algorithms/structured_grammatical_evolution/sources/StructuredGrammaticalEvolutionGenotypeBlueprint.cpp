//
// Created by mihael on 5/31/24.
//

#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"

#include <climits>

#include "SGEGrammar.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

StructuredGrammaticalEvolutionGenotypeBlueprint::StructuredGrammaticalEvolutionGenotypeBlueprint(int max_depth, double constant_min, double constant_max) {
    this->max_depth = max_depth;
    this->grammar = new SGEGrammar();
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

double StructuredGrammaticalEvolutionGenotypeBlueprint::generateConstant() {
    return constant_generator->generate();
}

int StructuredGrammaticalEvolutionGenotypeBlueprint::generateCodonValue(int possible_values) {
    return generator->generate() % possible_values;
}
