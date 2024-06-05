//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningGenotypeBlueprint.h"

#include <climits>
#include <utility>

#include "UniformIntDistributionGenerator.h"

HyperparameterTuningGenotypeBlueprint::HyperparameterTuningGenotypeBlueprint(
    std::vector<std::string> hyperparameters,
    std::map<std::string, std::vector<hyperparameter_value>> hyperparameter_domains
) {
    this->hyperparameters = std::move(hyperparameters);
    this->hyperparameter_domains = std::move(hyperparameter_domains);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

hyperparameter_value HyperparameterTuningGenotypeBlueprint::generateHyperparameterValue(const std::string& hyperparameter) {
    auto domain = hyperparameter_domains[hyperparameter];
    return domain[generator->generate() % domain.size()];
}

