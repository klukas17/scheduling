//
// Created by mihael on 6/1/24.
//

#ifndef GRAPHBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#define GRAPHBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "GraphBasedGeneticProgrammingGenotypeBlueprint.h"


class GraphBasedGeneticProgrammingCombinationOperator final : public CombinationOperator {
    GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    int max_number_of_nodes_to_crossover;
    double proceed_in_branch_chance;
    IntegerGenerator* generator;
    DoubleGenerator* chance_generator;
public:
    GraphBasedGeneticProgrammingCombinationOperator(
        GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint,
        int max_number_of_nodes_to_crossover,
        double proceed_in_branch_chance
    );
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //GRAPHBASEDGENETICPROGRAMMINGCOMBINATIONOPERATOR_H
