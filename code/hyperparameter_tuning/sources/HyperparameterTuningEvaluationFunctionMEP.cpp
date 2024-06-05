//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionMEP.h"

#include <utility>

#include "MultiExpressionProgrammingCombinationOperator.h"
#include "MultiExpressionProgrammingCreationOperator.h"
#include "MultiExpressionProgrammingGenotypeBlueprint.h"
#include "MultiExpressionProgrammingPerturbationOperator.h"
#include "MultiExpressionProgrammingSerializationOperator.h"

HyperparameterTuningEvaluationFunctionMEP::HyperparameterTuningEvaluationFunctionMEP(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionMEP::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new MultiExpressionProgrammingGenotypeBlueprint(
        std::get<int>(htg->hyperparameter_values["mep_number_of_instructions"]),
        -1,
        1
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionMEP::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new MultiExpressionProgrammingCreationOperator(
        dynamic_cast<MultiExpressionProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionMEP::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new MultiExpressionProgrammingCombinationOperator(
        dynamic_cast<MultiExpressionProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionMEP::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new MultiExpressionProgrammingPerturbationOperator(
        dynamic_cast<MultiExpressionProgrammingGenotypeBlueprint*>(this->blueprint),
        std::get<double>(htg->hyperparameter_values["mep_perturbation_rate"])
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionMEP::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new MultiExpressionProgrammingSerializationOperator(
        dynamic_cast<MultiExpressionProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}