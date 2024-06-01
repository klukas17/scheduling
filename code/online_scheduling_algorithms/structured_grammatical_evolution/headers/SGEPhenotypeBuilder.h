//
// Created by mihael on 5/31/24.
//

#ifndef SGEPHENOTYPEBUILDER_H
#define SGEPHENOTYPEBUILDER_H
#include "SGEPhenotypeNode.h"
#include "StructuredGrammaticalEvolution.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"


class SGEPhenotypeBuilder {
    static void buildPhenotypeNode(
        SGEPhenotypeNode* node,
        StructuredGrammaticalEvolution* sge,
        StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint,
        const std::map<int, double>& prepopulated_constants_map,
        int& codon_index,
        int& node_id,
        int& symbol_values_index,
        int& terminal_values_index,
        int& nonterminal_values_index,
        int& param_values_index
    );
public:
    static void buildPhenotype(
        StructuredGrammaticalEvolution* sge,
        StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint,
        const std::map<int, double>& prepopulated_constants_map
    );
};



#endif //SGEPHENOTYPEBUILDER_H
