//
// Created by mihael on 5/29/24.
//

#ifndef STACKBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#define STACKBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "IntegerGenerator.h"
#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"


class StackBasedGeneticProgrammingCombinationOperator final : public CombinationOperator {
    StackBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit StackBasedGeneticProgrammingCombinationOperator(StackBasedGeneticProgrammingGenotypeBlueprint* blueprint);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //STACKBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
