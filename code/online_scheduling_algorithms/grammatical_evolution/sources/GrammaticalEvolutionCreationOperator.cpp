//
// Created by mihael on 5/30/24.
//

#include "GrammaticalEvolutionCreationOperator.h"

#include "GEGenotypeNode.h"
#include "GEPhenotypeBuilder.h"
#include "GEProgram.h"
#include "GrammaticalEvolution.h"

GrammaticalEvolutionCreationOperator::GrammaticalEvolutionCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<GrammaticalEvolutionGenotypeBlueprint*>(genotype_blueprint);
}

Genotype* GrammaticalEvolutionCreationOperator::create() {

    std::vector<GEGenotypeNode*> genotype_nodes;
    genotype_nodes.reserve(blueprint->codons);

    for (int i = 0; i < blueprint->codons; i++) {
        auto codon_value = blueprint->generateCodonValue();
        genotype_nodes.push_back(new GEGenotypeNode(i, codon_value));
    }

    auto program = new GEProgram(genotype_nodes);
    auto ge = new GrammaticalEvolution(program);
    ge->setInputs(blueprint->getInputs());
    GEPhenotypeBuilder::buildPhenotype(ge, blueprint, {});
    return ge;
}

