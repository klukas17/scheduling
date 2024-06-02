//
// Created by mihael on 6/1/24.
//

#ifndef GRAPHBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
#define GRAPHBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "GraphBasedGeneticProgrammingGenotypeBlueprint.h"
#include "IntegerGenerator.h"


class GraphBasedGeneticProgrammingCreationOperator final : public CreationOperator {
    GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit GraphBasedGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint);
    Genotype* create() override;
};



#endif //GRAPHBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
