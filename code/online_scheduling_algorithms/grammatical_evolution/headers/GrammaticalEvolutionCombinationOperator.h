//
// Created by mihael on 5/30/24.
//

#ifndef GRAMMATICALEVOLUTIONCOMBINATIONOPERATOR_H
#define GRAMMATICALEVOLUTIONCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "GrammaticalEvolutionGenotypeBlueprint.h"


class GrammaticalEvolutionCombinationOperator final : public CombinationOperator {
    GrammaticalEvolutionGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit GrammaticalEvolutionCombinationOperator(GrammaticalEvolutionGenotypeBlueprint* blueprint);
    ~GrammaticalEvolutionCombinationOperator() override;
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //GRAMMATICALEVOLUTIONCOMBINATIONOPERATOR_H
