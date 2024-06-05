//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningCombinationOperator.h"

#include "HyperparameterTuningGenotype.h"
#include "UniformIntDistributionGenerator.h"

HyperparameterTuningCombinationOperator::HyperparameterTuningCombinationOperator(HyperparameterTuningGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, 1);
}

Genotype* HyperparameterTuningCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto htg1 = dynamic_cast<HyperparameterTuningGenotype*>(genotype1);
    auto htg2 = dynamic_cast<HyperparameterTuningGenotype*>(genotype2);

    auto hyperparameters = blueprint->hyperparameters;
    std::map<std::string, hyperparameter_value> hyperparameter_values;

    for (const auto& hyperparameter : hyperparameters) {
        hyperparameter_values[hyperparameter] = generator->generate() == 0 ?
            htg1->hyperparameter_values[hyperparameter] :
            htg2->hyperparameter_values[hyperparameter];
    }

    return new HyperparameterTuningGenotype(hyperparameters, hyperparameter_values);
}
