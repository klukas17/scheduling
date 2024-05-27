//
// Created by mihael on 5/23/24.
//

#ifndef CARTESIANGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#define CARTESIANGENETICPROGRAMMINGCOMBINATIONOPERATOR_H

#include "CartesianGeneticProgrammingGenotypeBlueprint.h"
#include "CombinationOperator.h"
#include "IntegerGenerator.h"


class CartesianGeneticProgrammingCombinationOperator final : public CombinationOperator {
    CartesianGeneticProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit CartesianGeneticProgrammingCombinationOperator(CartesianGeneticProgrammingGenotypeBlueprint* blueprint);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //CARTESIANGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
