//
// Created by mihael on 5/23/24.
//

#ifndef CARTESIANGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#define CARTESIANGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#include "CartesianGeneticProgrammingGenotypeBlueprint.h"
#include "IntegerGenerator.h"
#include "PerturbationOperator.h"


class CartesianGeneticProgrammingPerturbationOperator final : public PerturbationOperator {
    CartesianGeneticProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
    double perturbation_rate;
public:
    CartesianGeneticProgrammingPerturbationOperator(CartesianGeneticProgrammingGenotypeBlueprint* blueprint, double perturbation_rate);
    void perturbate(Genotype* genotype) override;
};



#endif //CARTESIANGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
