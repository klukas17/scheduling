//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGPERTURBATIONOPERATOR_H
#define HYPERPARAMETERTUNINGPERTURBATIONOPERATOR_H
#include "HyperparameterTuningGenotypeBlueprint.h"
#include "PerturbationOperator.h"


class HyperparameterTuningPerturbationOperator final : public PerturbationOperator {
public:
    HyperparameterTuningGenotypeBlueprint* blueprint;
    double perturbation_rate;
    IntegerGenerator* generator;
    HyperparameterTuningPerturbationOperator(HyperparameterTuningGenotypeBlueprint* blueprint, double perturbation_rate);
    void perturbate(Genotype* genotype) override;
};



#endif //HYPERPARAMETERTUNINGPERTURBATIONOPERATOR_H
