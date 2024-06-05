//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionSBGP.h"

#include <utility>

#include "StackBasedGeneticProgrammingCombinationOperator.h"
#include "StackBasedGeneticProgrammingCreationOperator.h"
#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"
#include "StackBasedGeneticProgrammingPerturbationOperator.h"
#include "StackBasedGeneticProgrammingSerializationOperator.h"

HyperparameterTuningEvaluationFunctionSBGP::HyperparameterTuningEvaluationFunctionSBGP(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionSBGP::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new StackBasedGeneticProgrammingGenotypeBlueprint(
        std::get<int>(htg->hyperparameter_values["sbgp_number_of_instructions"]),
        std::get<double>(htg->hyperparameter_values["sbgp_initialization_chance_of_nop"]),
        std::get<double>(htg->hyperparameter_values["sbgp_push_constant_share"]),
        std::get<double>(htg->hyperparameter_values["sbgp_push_param_share"]),
        -1,
        1
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionSBGP::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new StackBasedGeneticProgrammingCreationOperator(
        dynamic_cast<StackBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionSBGP::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new StackBasedGeneticProgrammingCombinationOperator(
        dynamic_cast<StackBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionSBGP::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new StackBasedGeneticProgrammingPerturbationOperator(
        dynamic_cast<StackBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint),
        std::get<double>(htg->hyperparameter_values["sbgp_perturbation_rate"]),
        std::get<double>(htg->hyperparameter_values["sbgp_perturbation_chance_of_nop"])
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionSBGP::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new StackBasedGeneticProgrammingSerializationOperator(
        dynamic_cast<StackBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}