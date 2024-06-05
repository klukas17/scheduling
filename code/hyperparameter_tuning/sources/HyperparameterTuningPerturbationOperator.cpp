//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningPerturbationOperator.h"

#include <climits>

#include "HyperparameterTuningGenotype.h"
#include "UniformIntDistributionGenerator.h"

HyperparameterTuningPerturbationOperator::HyperparameterTuningPerturbationOperator(HyperparameterTuningGenotypeBlueprint* blueprint, double perturbation_rate) {
    this->blueprint = blueprint;
    this->perturbation_rate = perturbation_rate;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

void HyperparameterTuningPerturbationOperator::perturbate(Genotype* genotype) {
    auto htg = dynamic_cast<HyperparameterTuningGenotype*>(genotype);

    auto changes = perturbation_rate * htg->hyperparameters.size();

    for (int i = 0; i < changes; i++) {
        auto hyperparameter_index = generator->generate() % htg->hyperparameters.size();
        auto hyperparameter = htg->hyperparameters[hyperparameter_index];
        htg->hyperparameter_values[hyperparameter] = blueprint->generateHyperparameterValue(hyperparameter);
    }
}
