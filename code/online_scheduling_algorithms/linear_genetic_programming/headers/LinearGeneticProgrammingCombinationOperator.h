//
// Created by mihael on 5/27/24.
//

#ifndef LINEARGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#define LINEARGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "LinearGeneticProgrammingGenotypeBlueprint.h"


class LinearGeneticProgrammingCombinationOperator final : public CombinationOperator {
    LinearGeneticProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit LinearGeneticProgrammingCombinationOperator(LinearGeneticProgrammingGenotypeBlueprint* blueprint);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //LINEARGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
