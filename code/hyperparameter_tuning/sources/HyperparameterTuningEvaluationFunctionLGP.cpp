//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunctionLGP.h"

#include <utility>

#include "LGPRegisterInitializationStrategyCircularLoading.h"
#include "LGPRegisterInitializationStrategyEmptyLoading.h"
#include "LGPRegisterInitializationStrategySingularLoading.h"
#include "LinearGeneticProgrammingCombinationOperator.h"
#include "LinearGeneticProgrammingCreationOperator.h"
#include "LinearGeneticProgrammingGenotypeBlueprint.h"
#include "LinearGeneticProgrammingPerturbationOperator.h"
#include "LinearGeneticProgrammingSerializationOperator.h"

HyperparameterTuningEvaluationFunctionLGP::HyperparameterTuningEvaluationFunctionLGP(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : HyperparameterTuningEvaluationFunction(topology, std::move(jobs_train_set), std::move(jobs_test_set), number_of_evaluations) {}

GenotypeBlueprint* HyperparameterTuningEvaluationFunctionLGP::constructGenotypeBlueprint(HyperparameterTuningGenotype* htg) {

    LGPRegisterInitializationStrategy* strategy = nullptr;
    auto strategy_name = std::get<std::string>(htg->hyperparameter_values["lgp_register_initialization_strategy"]);

    if (strategy_name == "empty") {
        strategy = new LGPRegisterInitializationStrategyEmptyLoading();
    } else if (strategy_name == "singular") {
        strategy = new LGPRegisterInitializationStrategySingularLoading();
    } else if (strategy_name == "circular") {
        strategy = new LGPRegisterInitializationStrategyCircularLoading();
    }

    return new LinearGeneticProgrammingGenotypeBlueprint(
        strategy,
        std::get<int>(htg->hyperparameter_values["lgp_number_of_registers"]),
        std::get<int>(htg->hyperparameter_values["lgp_number_of_instructions"]),
        std::get<double>(htg->hyperparameter_values["lgp_initialization_chance_of_nop"]),
        -1,
        1
    );
}

CreationOperator* HyperparameterTuningEvaluationFunctionLGP::constructCreationOperator(HyperparameterTuningGenotype* htg) {
    return new LinearGeneticProgrammingCreationOperator(
        dynamic_cast<LinearGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

CombinationOperator* HyperparameterTuningEvaluationFunctionLGP::constructCombinationOperator(HyperparameterTuningGenotype* htg) {
    return new LinearGeneticProgrammingCombinationOperator(
        dynamic_cast<LinearGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}

PerturbationOperator* HyperparameterTuningEvaluationFunctionLGP::constructPerturbationOperator(HyperparameterTuningGenotype* htg) {
    return new LinearGeneticProgrammingPerturbationOperator(
        dynamic_cast<LinearGeneticProgrammingGenotypeBlueprint*>(this->blueprint),
        std::get<double>(htg->hyperparameter_values["lgp_perturbation_rate"]),
        std::get<double>(htg->hyperparameter_values["lgp_perturbation_chance_of_nop"])
    );
}

SerializationOperator* HyperparameterTuningEvaluationFunctionLGP::constructSerializationOperator(HyperparameterTuningGenotype* htg) {
    return new LinearGeneticProgrammingSerializationOperator(
        dynamic_cast<LinearGeneticProgrammingGenotypeBlueprint*>(this->blueprint)
    );
}