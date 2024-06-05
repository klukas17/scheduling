//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGCOMBINATIONOPERATOR_H
#define HYPERPARAMETERTUNINGCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "HyperparameterTuningGenotypeBlueprint.h"


class HyperparameterTuningCombinationOperator final : public CombinationOperator {
public:
    HyperparameterTuningGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
    explicit HyperparameterTuningCombinationOperator(HyperparameterTuningGenotypeBlueprint* blueprint);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //HYPERPARAMETERTUNINGCOMBINATIONOPERATOR_H
