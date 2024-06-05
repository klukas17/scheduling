//
// Created by mihael on 5/30/24.
//

#include "GrammaticalEvolutionCombinationOperator.h"

#include <climits>

#include "GEPhenotypeBuilder.h"
#include "GrammaticalEvolution.h"
#include "UniformIntDistributionGenerator.h"

GrammaticalEvolutionCombinationOperator::GrammaticalEvolutionCombinationOperator(GrammaticalEvolutionGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

GrammaticalEvolutionCombinationOperator::~GrammaticalEvolutionCombinationOperator() {
    delete generator;
}

Genotype* GrammaticalEvolutionCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto ge1 = dynamic_cast<GrammaticalEvolution*>(genotype1);
    auto ge2 = dynamic_cast<GrammaticalEvolution*>(genotype2);

    auto program1 = ge1->getProgram();
    auto program2 = ge2->getProgram();

    auto inputs = ge1->getInputs();

    auto break_point = generator->generate() % (blueprint->codons - 1);

    std::vector<GEGenotypeNode*> nodes;
    nodes.reserve(blueprint->codons);

    for (int i = 0; i <= break_point; i++) {
        nodes.push_back(program1->genotype_nodes[i]->copy());
    }

    for (int i = break_point + 1; i < blueprint->codons; i++) {
        nodes.push_back(program2->genotype_nodes[i]->copy());
    }

    auto program = new GEProgram(nodes);
    auto ge = new GrammaticalEvolution(program);
    ge->setInputs(inputs);
    GEPhenotypeBuilder::buildPhenotype(ge, blueprint, {});
    return ge;
}
