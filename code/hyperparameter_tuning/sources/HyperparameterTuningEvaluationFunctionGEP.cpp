//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionGEP.h"

#include <utility>

#include "GeneExpressionProgrammingCombinationOperator.h"
#include "GeneExpressionProgrammingCreationOperator.h"
#include "GeneExpressionProgrammingGenotypeBlueprint.h"
#include "GeneExpressionProgrammingPerturbationOperator.h"
#include "GeneExpressionProgrammingSerializationOperator.h"

HyperparameterTuningEvaluationFunctionGEP::HyperparameterTuningEvaluationFunctionGEP(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionGEP::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new GeneExpressionProgrammingGenotypeBlueprint(
        std::get<int>(htg->hyperparameter_values["gep_head_size"]),
        std::get<double>(htg->hyperparameter_values["gep_tail_chance_of_param"]),
        -1,
        1
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionGEP::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new GeneExpressionProgrammingCreationOperator(
        dynamic_cast<GeneExpressionProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionGEP::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new GeneExpressionProgrammingCombinationOperator(
        dynamic_cast<GeneExpressionProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionGEP::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new GeneExpressionProgrammingPerturbationOperator(
        dynamic_cast<GeneExpressionProgrammingGenotypeBlueprint*>(this->blueprint),
        std::get<double>(htg->hyperparameter_values["gep_perturbation_rate"]),
        std::get<double>(htg->hyperparameter_values["gep_chance_of_transposition"]),
        std::get<int>(htg->hyperparameter_values["gep_transposition_max_length"])
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionGEP::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new GeneExpressionProgrammingSerializationOperator(
        dynamic_cast<GeneExpressionProgrammingGenotypeBlueprint*>(blueprint)
    );
}