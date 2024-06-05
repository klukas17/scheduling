//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionNN.h"

#include <utility>

#include "NeuralNetworkCombinationOperator.h"
#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"
#include "NeuralNetworkPerturbationOperator.h"
#include "NeuralNetworkSerializationOperator.h"
#include "NormalDistribution.h"

HyperparameterTuningEvaluationFunctionNN::HyperparameterTuningEvaluationFunctionNN(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionNN::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {
    return new NeuralNetworkGenotypeBlueprint(
        new NormalDistribution(0, std::get<double>(htg->hyperparameter_values["nn_creation_sigma"])),
        std::get<std::vector<int>>(htg->hyperparameter_values["nn_layer_sizes"]),
        std::get<std::string>(htg->hyperparameter_values["nn_activation_function_name"])
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionNN::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new NeuralNetworkCreationOperator(
        dynamic_cast<NeuralNetworkGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionNN::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new NeuralNetworkCombinationOperator();
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionNN::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new NeuralNetworkPerturbationOperator(
        new NormalDistribution(0, std::get<double>(htg->hyperparameter_values["nn_perturbation_sigma"]))
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionNN::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new NeuralNetworkSerializationOperator(
        dynamic_cast<NeuralNetworkGenotypeBlueprint*>(this->blueprint)
    );
}