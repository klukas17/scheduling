//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionGBGP.h"

#include <utility>

#include "GraphBasedGeneticProgrammingCombinationOperator.h"
#include "GraphBasedGeneticProgrammingCreationOperator.h"
#include "GraphBasedGeneticProgrammingGenotypeBlueprint.h"
#include "GraphBasedGeneticProgrammingPerturbationOperator.h"
#include "GraphBasedGeneticProgrammingSerializationOperator.h"

HyperparameterTuningEvaluationFunctionGBGP::HyperparameterTuningEvaluationFunctionGBGP(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionGBGP::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new GraphBasedGeneticProgrammingGenotypeBlueprint(
        std::get<int>(htg->hyperparameter_values["gbgp_max_number_of_nodes"]),
        -1,
        1
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionGBGP::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new GraphBasedGeneticProgrammingCreationOperator(
        dynamic_cast<GraphBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionGBGP::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new GraphBasedGeneticProgrammingCombinationOperator(
        dynamic_cast<GraphBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint),
        std::get<int>(htg->hyperparameter_values["gbgp_max_number_of_nodes_to_crossover"]),
        std::get<double>(htg->hyperparameter_values["gbgp_proceed_in_branch_chance"])
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionGBGP::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new GraphBasedGeneticProgrammingPerturbationOperator(
        dynamic_cast<GraphBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint),
        std::get<double>(htg->hyperparameter_values["gbgp_perturbation_rate"]),
        std::get<int>(htg->hyperparameter_values["gbgp_max_nodes_to_delete"]),
        std::get<int>(htg->hyperparameter_values["gbgp_max_nodes_to_insert"])
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionGBGP::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new GraphBasedGeneticProgrammingSerializationOperator(
        dynamic_cast<GraphBasedGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}