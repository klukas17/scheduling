//
// Created by mihael on 5/21/24.
//

#ifndef TREEBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#define TREEBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "IntegerGenerator.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"


class TreeBasedGeneticProgrammingCombinationOperator final : public CombinationOperator {
    TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit TreeBasedGeneticProgrammingCombinationOperator(TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //TREEBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
