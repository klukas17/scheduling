//
// Created by mihael on 5/30/24.
//

#include "GrammaticalEvolutionPerturbationOperator.h"

#include <climits>

#include "GEPhenotypeBuilder.h"
#include "GrammaticalEvolution.h"
#include "UniformIntDistributionGenerator.h"

GrammaticalEvolutionPerturbationOperator::GrammaticalEvolutionPerturbationOperator(GrammaticalEvolutionGenotypeBlueprint* blueprint, double perturbation_rate) {
    this->blueprint = blueprint;
    this->perturabtion_rate = perturbation_rate;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

GrammaticalEvolutionPerturbationOperator::~GrammaticalEvolutionPerturbationOperator() {
    delete generator;
}

void GrammaticalEvolutionPerturbationOperator::perturbate(Genotype* genotype) {
    auto ge = dynamic_cast<GrammaticalEvolution*>(genotype);
    auto program = ge->getProgram();
    auto changes = blueprint->codons * perturabtion_rate;

    for (int i = 0; i < changes; i++) {
        auto node_index = generator->generate() % blueprint->codons;
        auto node = program->genotype_nodes[node_index];
        node->codon_value = blueprint->generateCodonValue();
    }

    GEPhenotypeBuilder::buildPhenotype(ge, blueprint, {});
}
