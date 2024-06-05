//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningCreationOperator.h"

#include "HyperparameterTuningGenotype.h"

HyperparameterTuningCreationOperator::HyperparameterTuningCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<HyperparameterTuningGenotypeBlueprint*>(genotype_blueprint);
}

Genotype* HyperparameterTuningCreationOperator::create() {
    auto hyperparameters = blueprint->hyperparameters;
    std::map<std::string, hyperparameter_value> hyperparameter_values;

    for (const auto& hyperparameter : hyperparameters) {
        hyperparameter_values[hyperparameter] = blueprint->generateHyperparameterValue(hyperparameter);
    }

    return new HyperparameterTuningGenotype(hyperparameters, hyperparameter_values);
}
