//
// Created by mihael on 5/31/24.
//

#include "StructuredGrammaticalEvolutionPerturbationOperator.h"

#include <climits>

#include "SGEPhenotypeBuilder.h"
#include "StructuredGrammaticalEvolution.h"
#include "UniformIntDistributionGenerator.h"

StructuredGrammaticalEvolutionPerturbationOperator::StructuredGrammaticalEvolutionPerturbationOperator(StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint, double perturbation_rate) {
    this->blueprint = blueprint;
    this->perturbation_rate = perturbation_rate;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

void StructuredGrammaticalEvolutionPerturbationOperator::perturbate(Genotype* genotype) {

    auto sge = dynamic_cast<StructuredGrammaticalEvolution*>(genotype);
    auto program = sge->getProgram();
    auto metadata = program->metadata;

    auto symbol_values = program->symbol_values.size();
    for (int i = 0; i < perturbation_rate * symbol_values; i++) {
        auto index = generator->generate() % symbol_values;
        program->symbol_values[index] = blueprint->generateCodonValue(metadata->possible_values[SGE_SYMBOL]);
    }

    auto terminal_values = program->terminal_values.size();
    for (int i = 0; i < perturbation_rate * terminal_values; i++) {
        auto index = generator->generate() % terminal_values;
        program->terminal_values[index] = blueprint->generateCodonValue(metadata->possible_values[SGE_TERMINAL]);
    }

    auto nonterminal_values = program->nonterminal_values.size();
    for (int i = 0; i < perturbation_rate * nonterminal_values; i++) {
        auto index = generator->generate() % nonterminal_values;
        program->nonterminal_values[index] = blueprint->generateCodonValue(metadata->possible_values[SGE_NONTERMINAL]);
    }

    auto param_values = program->param_values.size();
    for (int i = 0; i < perturbation_rate * param_values; i++) {
        auto index = generator->generate() % param_values;
        program->param_values[index] = blueprint->generateCodonValue(metadata->possible_values[SGE_PARAM]);
    }

    SGEPhenotypeBuilder::buildPhenotype(sge, blueprint, {});
}
