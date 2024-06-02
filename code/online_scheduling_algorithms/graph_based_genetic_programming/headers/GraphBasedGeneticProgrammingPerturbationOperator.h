//
// Created by mihael on 6/1/24.
//

#ifndef GRAPHBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#define GRAPHBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#include "GraphBasedGeneticProgrammingGenotypeBlueprint.h"
#include "PerturbationOperator.h"


class GraphBasedGeneticProgrammingPerturbationOperator final : public PerturbationOperator {
    GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    double perturbation_rate;
    int max_nodes_to_delete;
    int max_nodes_to_insert;
    DoubleGenerator* chance_generator;
    IntegerGenerator* generator;
public:
    GraphBasedGeneticProgrammingPerturbationOperator(
        GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint,
        double perturbation_rate,
        int max_nodes_to_delete,
        int max_nodes_to_insert
    );
    void perturbate(Genotype* genotype) override;
};



#endif //GRAPHBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
