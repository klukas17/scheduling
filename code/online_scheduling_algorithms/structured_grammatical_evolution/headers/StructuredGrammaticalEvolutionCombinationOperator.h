//
// Created by mihael on 5/31/24.
//

#ifndef STRUCTUREDGRAMMATICALEVOLUTIONCOMBINATIONOPERATOR_H
#define STRUCTUREDGRAMMATICALEVOLUTIONCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"


class StructuredGrammaticalEvolutionCombinationOperator final : public CombinationOperator {
    StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit StructuredGrammaticalEvolutionCombinationOperator(StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //STRUCTUREDGRAMMATICALEVOLUTIONCOMBINATIONOPERATOR_H
