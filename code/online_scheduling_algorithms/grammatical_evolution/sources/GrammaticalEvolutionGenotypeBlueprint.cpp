//
// Created by mihael on 5/30/24.
//

#include "GrammaticalEvolutionGenotypeBlueprint.h"

#include <climits>

#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

GrammaticalEvolutionGenotypeBlueprint::GrammaticalEvolutionGenotypeBlueprint(
    int codons,
    int codon_values,
    int max_number_of_wrapping,
    double constant_min,
    double constant_max
) {
    this->codons = codons;
    this->codon_values = codon_values;
    this->max_number_of_wrapping = max_number_of_wrapping;
    this->grammar = new GEGrammar();
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

double GrammaticalEvolutionGenotypeBlueprint::generateConstant() {
    return constant_generator->generate();
}

std::string GrammaticalEvolutionGenotypeBlueprint::generateParam(std::vector<std::string> params) {
    return params[generator->generate() % params.size()];
}

int GrammaticalEvolutionGenotypeBlueprint::generateCodonValue() {
    return generator->generate() % codon_values;
}
