//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionTBGP.h"

#include <utility>

#include "TreeBasedGeneticProgrammingCombinationOperator.h"
#include "TreeBasedGeneticProgrammingCreationOperator.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"
#include "TreeBasedGeneticProgrammingPerturbationOperator.h"
#include "TreeBasedGeneticProgrammingSerializationOperator.h"

HyperparameterTuningEvaluationFunctionTBGP::HyperparameterTuningEvaluationFunctionTBGP(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionTBGP::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new TreeBasedGeneticProgrammingGenotypeBlueprint(
        new TBGPNodeFactory(
            std::get<double>(htg->hyperparameter_values["tbgp_leaf_const_chance"]),
            std::get<double>(htg->hyperparameter_values["tbgp_leaf_param_chance"]),
            -1,
            1
        ),
        std::get<int>(htg->hyperparameter_values["tbgp_max_height"])
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionTBGP::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new TreeBasedGeneticProgrammingCreationOperator(
        dynamic_cast<TreeBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionTBGP::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new TreeBasedGeneticProgrammingCombinationOperator(
        dynamic_cast<TreeBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionTBGP::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new TreeBasedGeneticProgrammingPerturbationOperator(
        dynamic_cast<TreeBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionTBGP::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new TreeBasedGeneticProgrammingSerializationOperator(
        dynamic_cast<TreeBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}