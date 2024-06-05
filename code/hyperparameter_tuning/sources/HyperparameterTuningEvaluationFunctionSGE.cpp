//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionSGE.h"

#include <utility>

#include "StructuredGrammaticalEvolutionCombinationOperator.h"
#include "StructuredGrammaticalEvolutionCreationOperator.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"
#include "StructuredGrammaticalEvolutionPerturbationOperator.h"
#include "StructuredGrammaticalEvolutionSerializationOperator.h"

HyperparameterTuningEvaluationFunctionSGE::HyperparameterTuningEvaluationFunctionSGE(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionSGE::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new StructuredGrammaticalEvolutionGenotypeBlueprint(
        std::get<int>(htg->hyperparameter_values["sge_max_depth"]),
        -1,
        1
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionSGE::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new StructuredGrammaticalEvolutionCreationOperator(
        dynamic_cast<StructuredGrammaticalEvolutionGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionSGE::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new StructuredGrammaticalEvolutionCombinationOperator(
        dynamic_cast<StructuredGrammaticalEvolutionGenotypeBlueprint*>(this->blueprint)
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionSGE::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new StructuredGrammaticalEvolutionPerturbationOperator(
        dynamic_cast<StructuredGrammaticalEvolutionGenotypeBlueprint*>(this->blueprint),
        std::get<double>(htg->hyperparameter_values["sge_perturbation_rate"])
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionSGE::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new StructuredGrammaticalEvolutionSerializationOperator(
        dynamic_cast<StructuredGrammaticalEvolutionGenotypeBlueprint*>(this->blueprint)
    );
}