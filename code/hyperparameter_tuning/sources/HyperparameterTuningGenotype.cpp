//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningGenotype.h"

#include <utility>

HyperparameterTuningGenotype::HyperparameterTuningGenotype(
    std::vector<std::string> hyperparameters,
    std::map<std::string, hyperparameter_value> hyperparameter_values
) {
    this->hyperparameters = std::move(hyperparameters);
    this->hyperparameter_values = std::move(hyperparameter_values);
}

Genotype* HyperparameterTuningGenotype::copy() {
    return new HyperparameterTuningGenotype(hyperparameters, hyperparameter_values);
}
