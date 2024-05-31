//
// Created by mihael on 5/31/24.
//

#ifndef GEPHENOTYPEBUILDER_H
#define GEPHENOTYPEBUILDER_H
#include "GrammaticalEvolution.h"
#include "GrammaticalEvolutionGenotypeBlueprint.h"


class GEPhenotypeBuilder {
    static void buildPhenotypeNode(
        GEPhenotypeNode* node,
        GrammaticalEvolution* ge,
        GrammaticalEvolutionGenotypeBlueprint* blueprint,
        const std::map<int, double>& prepopulated_constants_map,
        int& codon_index,
        int& number_of_wrappings,
        int& node_id,
        bool& mapping_failed
    );
public:
    static void buildPhenotype(
        GrammaticalEvolution* ge,
        GrammaticalEvolutionGenotypeBlueprint* blueprint,
        const std::map<int, double>& prepopulated_constants_map
    );
};



#endif //GEPHENOTYPEBUILDER_H
