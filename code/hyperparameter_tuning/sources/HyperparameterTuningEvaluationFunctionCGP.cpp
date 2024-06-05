//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionCGP.h"

#include <utility>

#include "CartesianGeneticProgrammingCombinationOperator.h"
#include "CartesianGeneticProgrammingCreationOperator.h"
#include "CartesianGeneticProgrammingGenotypeBlueprint.h"
#include "CartesianGeneticProgrammingPerturbationOperator.h"
#include "CartesianGeneticProgrammingSerializationOperator.h"

HyperparameterTuningEvaluationFunctionCGP::HyperparameterTuningEvaluationFunctionCGP(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionCGP::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new CartesianGeneticProgrammingGenotypeBlueprint(
        std::get<int>(htg->hyperparameter_values["cgp_rows"]),
        std::get<int>(htg->hyperparameter_values["cgp_cols"]),
        new CGPFunctionsIndex(),
        -1,
        1
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionCGP::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new CartesianGeneticProgrammingCreationOperator(
        dynamic_cast<CartesianGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionCGP::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new CartesianGeneticProgrammingCombinationOperator(
        dynamic_cast<CartesianGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionCGP::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new CartesianGeneticProgrammingPerturbationOperator(
        dynamic_cast<CartesianGeneticProgrammingGenotypeBlueprint*>(this->blueprint),
        std::get<double>(htg->hyperparameter_values["cgp_perturbation_rate"])
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionCGP::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new CartesianGeneticProgrammingSerializationOperator(
        dynamic_cast<CartesianGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}