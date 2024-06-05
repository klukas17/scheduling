//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningSerializationOperator.h"

#include "HyperparameterTuningGenotype.h"
#include "sstream"

HyperparameterTuningSerializationOperator::HyperparameterTuningSerializationOperator(HyperparameterTuningGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

std::vector<std::string> HyperparameterTuningSerializationOperator::serialize(Genotype* genotype) {
    auto htg = dynamic_cast<HyperparameterTuningGenotype*>(genotype);

    std::vector<std::string> result;

    for (const auto& hyperparameter : htg->hyperparameters) {
        std::ostringstream oss;
        oss << hyperparameter << " " << htg->hyperparameter_values[hyperparameter];
        result.push_back(oss.str());
    }

    return result;
}

Genotype* HyperparameterTuningSerializationOperator::deserialize(std::vector<std::string> representation) {
    auto hyperparameters = blueprint->hyperparameters;
    std::map<std::string, hyperparameter_value> hyperparameter_values;

    for (int i = 0; i < hyperparameters.size(); i++) {
        std::istringstream iss(representation[i]);
        std::string hyperparameter, hyperparameter_value;
        iss >> hyperparameter >> hyperparameter_value;
        hyperparameter_values[hyperparameter] = hyperparameter_value;
    }

    return new HyperparameterTuningGenotype(hyperparameters, hyperparameter_values);
}
