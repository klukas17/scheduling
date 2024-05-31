//
// Created by mihael on 5/30/24.
//

#ifndef GRAMMATICALEVOLUTIONSERIALIZATIONOPERATOR_H
#define GRAMMATICALEVOLUTIONSERIALIZATIONOPERATOR_H
#include "GEPhenotypeNode.h"
#include "GrammaticalEvolutionGenotypeBlueprint.h"
#include "SerializationOperatorWithDistinctPhenotype.h"


class GrammaticalEvolutionSerializationOperator : public SerializationOperatorWithDistinctPhenotype {
    GrammaticalEvolutionGenotypeBlueprint* blueprint;
    std::vector<std::string> serializePhenotypeNode(GEPhenotypeNode* node, int depth);
public:
    explicit GrammaticalEvolutionSerializationOperator(GrammaticalEvolutionGenotypeBlueprint* blueprint);
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
    std::vector<std::string> serializePhenotype(Genotype* genotype) override;
};



#endif //GRAMMATICALEVOLUTIONSERIALIZATIONOPERATOR_H
