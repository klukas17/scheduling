//
// Created by mihael on 5/31/24.
//

#ifndef STRUCTUREDGRAMMATICALEVOLUTIONSERIALIZATIONOPERATOR_H
#define STRUCTUREDGRAMMATICALEVOLUTIONSERIALIZATIONOPERATOR_H
#include "SerializationOperatorWithDistinctPhenotype.h"
#include "SGEPhenotypeNode.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"


class StructuredGrammaticalEvolutionSerializationOperator final : public SerializationOperatorWithDistinctPhenotype {
    StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint;
    std::vector<std::string> serializePhenotypeNode(SGEPhenotypeNode* node, int depth);
public:
    explicit StructuredGrammaticalEvolutionSerializationOperator(StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint);
    ~StructuredGrammaticalEvolutionSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
    std::vector<std::string> serializePhenotype(Genotype* genotype) override;
};



#endif //STRUCTUREDGRAMMATICALEVOLUTIONSERIALIZATIONOPERATOR_H
