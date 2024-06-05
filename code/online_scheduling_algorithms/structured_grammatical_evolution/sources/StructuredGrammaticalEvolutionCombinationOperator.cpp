//
// Created by mihael on 5/31/24.
//

#include "StructuredGrammaticalEvolutionCombinationOperator.h"

#include <climits>

#include "SGEPhenotypeBuilder.h"
#include "StructuredGrammaticalEvolution.h"
#include "UniformIntDistributionGenerator.h"

StructuredGrammaticalEvolutionCombinationOperator::StructuredGrammaticalEvolutionCombinationOperator(StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

StructuredGrammaticalEvolutionCombinationOperator::~StructuredGrammaticalEvolutionCombinationOperator() {
    delete generator;
}

Genotype* StructuredGrammaticalEvolutionCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto sge1 = dynamic_cast<StructuredGrammaticalEvolution*>(genotype1);
    auto sge2 = dynamic_cast<StructuredGrammaticalEvolution*>(genotype2);

    auto program1 = sge1->getProgram();
    auto program2 = sge2->getProgram();

    auto inputs = sge1->getInputs();

    auto program_metadata = new SGEProgramMetadata(blueprint->max_depth, inputs);

    auto program = new SGEProgram(
        program_metadata,
        generator->generate() % 2 == 0 ? program1->symbol_values : program2->symbol_values,
        generator->generate() % 2 == 0 ? program1->terminal_values : program2->terminal_values,
        generator->generate() % 2 == 0 ? program1->nonterminal_values : program2->nonterminal_values,
        generator->generate() % 2 == 0 ? program1->param_values : program2->param_values
    );
    auto sge = new StructuredGrammaticalEvolution(program);
    sge->setInputs(inputs);
    SGEPhenotypeBuilder::buildPhenotype(sge, blueprint, {});
    return sge;
}
