//
// Created by mihael on 5/30/24.
//

#ifndef GRAMMATICALEVOLUTIONPERTURBATIONOPERATOR_H
#define GRAMMATICALEVOLUTIONPERTURBATIONOPERATOR_H
#include "GrammaticalEvolutionGenotypeBlueprint.h"
#include "PerturbationOperator.h"


class GrammaticalEvolutionPerturbationOperator final : public PerturbationOperator {
    GrammaticalEvolutionGenotypeBlueprint* blueprint;
    double perturabtion_rate;
    IntegerGenerator* generator;
public:
    GrammaticalEvolutionPerturbationOperator(
        GrammaticalEvolutionGenotypeBlueprint* blueprint,
        double perturbation_rate
    );
    ~GrammaticalEvolutionPerturbationOperator() override;
    void perturbate(Genotype* genotype) override;
};



#endif //GRAMMATICALEVOLUTIONPERTURBATIONOPERATOR_H
