//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGCREATIONOPERATOR_H
#define HYPERPARAMETERTUNINGCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "HyperparameterTuningGenotypeBlueprint.h"


class HyperparameterTuningCreationOperator final : public CreationOperator {
public:
    HyperparameterTuningGenotypeBlueprint* blueprint;
    explicit HyperparameterTuningCreationOperator(GenotypeBlueprint* genotype_blueprint);
    Genotype* create() override;
};



#endif //HYPERPARAMETERTUNINGCREATIONOPERATOR_H
