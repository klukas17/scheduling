//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionGE.h"

#include <utility>

#include "GrammaticalEvolutionCombinationOperator.h"
#include "GrammaticalEvolutionCreationOperator.h"
#include "GrammaticalEvolutionGenotypeBlueprint.h"
#include "GrammaticalEvolutionPerturbationOperator.h"
#include "GrammaticalEvolutionSerializationOperator.h"

HyperparameterTuningEvaluationFunctionGE::HyperparameterTuningEvaluationFunctionGE(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionGE::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new GrammaticalEvolutionGenotypeBlueprint(
        std::get<int>(htg->hyperparameter_values["ge_codons"]),
        256,
        std::get<int>(htg->hyperparameter_values["ge_max_number_of_wrapping"]),
        -1,
        1
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionGE::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new GrammaticalEvolutionCreationOperator(
        dynamic_cast<GrammaticalEvolutionGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionGE::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new GrammaticalEvolutionCombinationOperator(
        dynamic_cast<GrammaticalEvolutionGenotypeBlueprint*>(this->blueprint)
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionGE::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new GrammaticalEvolutionPerturbationOperator(
        dynamic_cast<GrammaticalEvolutionGenotypeBlueprint*>(this->blueprint),
        std::get<double>(htg->hyperparameter_values["ge_perturbation_rate"])
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionGE::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new GrammaticalEvolutionSerializationOperator(
        dynamic_cast<GrammaticalEvolutionGenotypeBlueprint*>(this->blueprint)
    );
}