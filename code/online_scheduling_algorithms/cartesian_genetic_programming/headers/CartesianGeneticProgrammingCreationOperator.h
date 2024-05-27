//
// Created by mihael on 5/23/24.
//

#ifndef CARTESIANGENETICPROGRAMMINGCREATIONOPERATOR_H
#define CARTESIANGENETICPROGRAMMINGCREATIONOPERATOR_H
#include "CartesianGeneticProgrammingGenotypeBlueprint.h"
#include "CreationOperator.h"
#include "IntegerGenerator.h"


class CartesianGeneticProgrammingCreationOperator final : public CreationOperator {
    CartesianGeneticProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit CartesianGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint);
    Genotype* create() override;
};



#endif //CARTESIANGENETICPROGRAMMINGCREATIONOPERATOR_H
