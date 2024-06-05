//
// Created by mihael on 5/21/24.
//

#ifndef TREEBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
#define TREEBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"


class TreeBasedGeneticProgrammingCreationOperator final : public CreationOperator {
    TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint;
public:
    explicit TreeBasedGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint);
    ~TreeBasedGeneticProgrammingCreationOperator() override;
    Genotype* create() override;
};



#endif //TREEBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
