//
// Created by mihael on 5/31/24.
//

#include "StructuredGrammaticalEvolutionCreationOperator.h"

#include "SGEPhenotypeBuilder.h"
#include "SGEProgram.h"
#include "SGEProgramMetadata.h"
#include "StructuredGrammaticalEvolution.h"

StructuredGrammaticalEvolutionCreationOperator::StructuredGrammaticalEvolutionCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<StructuredGrammaticalEvolutionGenotypeBlueprint*>(genotype_blueprint);
}

StructuredGrammaticalEvolutionCreationOperator::~StructuredGrammaticalEvolutionCreationOperator() = default;

Genotype* StructuredGrammaticalEvolutionCreationOperator::create() {

    auto program_metadata = new SGEProgramMetadata(blueprint->max_depth, blueprint->getInputs());

    std::vector<int> symbol_values;
    std::vector<int> terminal_values;
    std::vector<int> nonterminal_values;
    std::vector<int> param_values;

    symbol_values.reserve(program_metadata->max_number_of_occurences[SGE_SYMBOL]);
    terminal_values.reserve(program_metadata->max_number_of_occurences[SGE_TERMINAL]);
    nonterminal_values.reserve(program_metadata->max_number_of_occurences[SGE_NONTERMINAL]);
    param_values.reserve(program_metadata->max_number_of_occurences[SGE_PARAM]);

    for (int i = 0; i < program_metadata->max_number_of_occurences[SGE_SYMBOL]; i++) {
        symbol_values.push_back(blueprint->generateCodonValue(program_metadata->possible_values[SGE_SYMBOL]));
    }

    for (int i = 0; i < program_metadata->max_number_of_occurences[SGE_TERMINAL]; i++) {
        terminal_values.push_back(blueprint->generateCodonValue(program_metadata->possible_values[SGE_TERMINAL]));
    }

    for (int i = 0; i < program_metadata->max_number_of_occurences[SGE_NONTERMINAL]; i++) {
        nonterminal_values.push_back(blueprint->generateCodonValue(program_metadata->possible_values[SGE_NONTERMINAL]));
    }

    for (int i = 0; i < program_metadata->max_number_of_occurences[SGE_PARAM]; i++) {
        param_values.push_back(blueprint->generateCodonValue(program_metadata->possible_values[SGE_PARAM]));
    }

    auto program = new SGEProgram(
        program_metadata,
        symbol_values,
        terminal_values,
        nonterminal_values,
        param_values
    );
    auto sge = new StructuredGrammaticalEvolution(program);
    sge->setInputs(blueprint->getInputs());
    SGEPhenotypeBuilder::buildPhenotype(sge, blueprint, {});
    return sge;
}

