//
// Created by mihael on 5/21/24.
//

#ifndef TREEBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#define TREEBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H

#include "IntegerGenerator.h"
#include "PerturbationOperator.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"


class TreeBasedGeneticProgrammingPerturbationOperator final : public PerturbationOperator {
    TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit TreeBasedGeneticProgrammingPerturbationOperator(TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint);
    ~TreeBasedGeneticProgrammingPerturbationOperator() override;
    void perturbate(Genotype* genotype) override;
};



#endif //TREEBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
