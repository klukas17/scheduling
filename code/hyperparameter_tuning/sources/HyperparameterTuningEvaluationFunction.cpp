//
// Created by mihael on 6/3/24.
//

#include "HyperparameterTuningEvaluationFunction.h"

#include <utility>

#include "BasicTopologyEnumerator.h"
#include "ClonalSelectionAlgorithm.h"
#include "DiscountedTotalWeightedCompletionTimeObjectiveFunction.h"
#include "EndToStartTopologyEnumerator.h"
#include "EvolutionStrategy.h"
#include "GenerationalGeneticAlgorithm.h"
#include "HyperparameterTuningCombinationOperator.h"
#include "HyperparameterTuningCreationOperator.h"
#include "HyperparameterTuningGenotype.h"
#include "HyperparameterTuningPerturbationOperator.h"
#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity.h"
#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity.h"
#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"
#include "OnlineSchedulingAlgorithmClusterPerturbationOperator.h"
#include "OnlineSchedulingAlgorithmClusterSerializationOperator.h"
#include "Population.h"
#include "RandomFairTopologyEnumerator.h"
#include "RandomPathTopologyEnumerator.h"
#include "RandomTopologyEnumerator.h"
#include "SchedulingEvaluationFunction.h"
#include "SchedulingMetaAlgorithm.h"
#include "SimpleImmunologicalAlgorithm.h"
#include "StartToEndTopologyEnumerator.h"
#include "SteadyStateGeneticAlgorithm.h"

HyperparameterTuningEvaluationFunction::HyperparameterTuningEvaluationFunction(
    Topology* topology,
    std::map<long, Job*> jobs_train_set,
    std::map<long, Job*> jobs_test_set,
    int number_of_evaluations
) : EvaluationFunction(true) {
    this->topology = topology;
    this->jobs_train_set = std::move(jobs_train_set);
    this->jobs_test_set = std::move(jobs_test_set);
    this->number_of_evaluations = number_of_evaluations;
    this->blueprint = nullptr;
}

double HyperparameterTuningEvaluationFunction::_evaluate(Genotype* genotype) {
    auto htg = dynamic_cast<HyperparameterTuningGenotype*>(genotype);

    auto iteration_count = extractIterationCount(htg);

    auto sub_population_size = extractSubPopulationSize(htg);
    auto population_size = 1;

    auto objective_function = new DiscountedTotalWeightedCompletionTimeObjectiveFunction();
    auto sub_evaluation_function = new SchedulingEvaluationFunction(
        objective_function,
        topology,
        jobs_train_set,
        false,
        ""
    );
    auto evaluation_function = new SchedulingEvaluationFunction(
        objective_function,
        topology,
        jobs_test_set,
        false,
        ""
    );

    this->blueprint = constructGenotypeBlueprint(htg);
    auto sub_creation_operator = constructCreationOperator(htg);
    auto sub_perturbation_operator = constructPerturbationOperator(htg);
    auto sub_combination_operator = constructCombinationOperator(htg);

    auto genotype_blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        genotype_blueprint,
        sub_creation_operator
    );
    auto perturbation_operator = new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto combination_operator = extractClusterCombinationOperator(htg, sub_combination_operator);
    auto topology_enumerator = extractTopologyEnumerator(htg, topology);

    auto sub_algorithm_population = new Population(sub_population_size);
    auto algorithm_population = new Population(population_size);

    auto sub_algorithm = extractSubAlgorithm(
        htg,
        sub_evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator
    );

    auto algorithm = new SchedulingMetaAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        topology_enumerator,
        sub_algorithm,
        sub_algorithm_population,
        iteration_count
    );

    algorithm->optimize(algorithm_population);

    auto score = algorithm_population->getGenotype(0)->fitness_score;

    delete objective_function;
    delete sub_evaluation_function;
    delete evaluation_function;
    delete sub_creation_operator;
    delete sub_combination_operator;
    delete sub_perturbation_operator;
    delete this->blueprint;
    this->blueprint = nullptr;
    delete genotype_blueprint;
    delete creation_operator;
    delete perturbation_operator;
    delete combination_operator;
    delete topology_enumerator;
    delete sub_algorithm_population;
    delete algorithm_population;
    delete sub_algorithm;
    delete algorithm;

    return score;
}

int HyperparameterTuningEvaluationFunction::extractIterationCount(HyperparameterTuningGenotype* htg) {

    auto alg = std::get<std::string>(htg->hyperparameter_values["optimization_algorithm"]);

    if (alg == "ssga") {
        return number_of_evaluations / std::get<int>(htg->hyperparameter_values["ssga_evaluations"]);
    }

    if (alg == "gga") {
        return number_of_evaluations / std::get<int>(htg->hyperparameter_values["gga_evaluations"]);
    }

    if (alg == "es") {
        return number_of_evaluations / std::get<int>(htg->hyperparameter_values["es_evaluations"]);
    }

    if (alg == "sia") {
        return number_of_evaluations / std::get<int>(htg->hyperparameter_values["sia_evaluations"]);
    }

    if (alg == "clonalg") {
        return number_of_evaluations / std::get<int>(htg->hyperparameter_values["clonalg_evaluations"]);
    }

    return 0;
}

int HyperparameterTuningEvaluationFunction::extractSubPopulationSize(HyperparameterTuningGenotype* htg) {
    auto alg = std::get<std::string>(htg->hyperparameter_values["optimization_algorithm"]);

    if (alg == "ssga") {
        return std::get<int>(htg->hyperparameter_values["ssga_population_size"]);
    }

    if (alg == "gga") {
        return std::get<int>(htg->hyperparameter_values["gga_population_size"]);
    }

    if (alg == "es") {
        return std::get<int>(htg->hyperparameter_values["es_population_size"]);
    }

    if (alg == "sia") {
        return std::get<int>(htg->hyperparameter_values["sia_population_size"]);
    }

    if (alg == "clonalg") {
        return std::get<int>(htg->hyperparameter_values["clonalg_population_size"]);
    }

    return 0;
}

OnlineSchedulingAlgorithmClusterCombinationOperator* HyperparameterTuningEvaluationFunction::extractClusterCombinationOperator(HyperparameterTuningGenotype* htg, CombinationOperator* sub_combination_operator) {

    auto granularity = std::get<std::string>(htg->hyperparameter_values["cluster_combination_operator_granularity"]);

    if (granularity == "coarse") {
        return new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(sub_combination_operator);
    }

    if (granularity == "fine") {
        return new OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity(sub_combination_operator);
    }

    return nullptr;
}

TopologyEnumerator* HyperparameterTuningEvaluationFunction::extractTopologyEnumerator(HyperparameterTuningGenotype* htg, Topology* topology) {

    int machines_with_algorithms = 0;
    for (auto [element_id, element] : topology->getTopologyElementsMap()) {
        auto element_type = element->getTopologyElementType();
        if (element_type == MACHINE_TOPOLOGY_ELEMENT || element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT || element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
            machines_with_algorithms++;
        }
    }

    auto enumerator_scheme = std::get<std::string>(htg->hyperparameter_values["topology_enumerator_scheme"]);

    if (enumerator_scheme == "all") {
        return new BasicTopologyEnumerator(topology);
    }

    if (enumerator_scheme == "1,beginning") {
        return new StartToEndTopologyEnumerator(topology, 1);
    }

    if (enumerator_scheme == "1,end") {
        return new EndToStartTopologyEnumerator(topology, 1);
    }

    if (enumerator_scheme == "1,random_fair") {
        return new RandomFairTopologyEnumerator(topology, 1);
    }

    if (enumerator_scheme == "1,random_true") {
        return new RandomTopologyEnumerator(topology, 1);
    }

    if (enumerator_scheme == "k,beginning") {
        return new StartToEndTopologyEnumerator(topology, std::round(std::sqrt(machines_with_algorithms)));
    }

    if (enumerator_scheme == "k,end") {
        return new EndToStartTopologyEnumerator(topology, std::round(std::sqrt(machines_with_algorithms)));
    }

    if (enumerator_scheme == "k,random_fair") {
        return new RandomFairTopologyEnumerator(topology, std::round(std::sqrt(machines_with_algorithms)));
    }

    if (enumerator_scheme == "k,random_true") {
        return new RandomTopologyEnumerator(topology, std::round(std::sqrt(machines_with_algorithms)));
    }

    if (enumerator_scheme == "random_path") {
        return new RandomPathTopologyEnumerator(topology, std::get<double>(htg->hyperparameter_values["random_path_topology_enumerator_change_element_chance"]));
    }

    return nullptr;
}

OptimizationAlgorithm* HyperparameterTuningEvaluationFunction::extractSubAlgorithm(
    HyperparameterTuningGenotype* htg,
    EvaluationFunction* evaluation_function,
    CreationOperator* creation_operator,
    PerturbationOperator* perturbation_operator,
    CombinationOperator* combination_operator
) {

    auto alg = std::get<std::string>(htg->hyperparameter_values["optimization_algorithm"]);

    if (alg == "ssga") {
        return new SteadyStateGeneticAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            combination_operator,
            std::get<int>(htg->hyperparameter_values["ssga_population_size"]),
            std::get<int>(htg->hyperparameter_values["ssga_evaluations"])
        );
    }

    if (alg == "gga") {
        return new GenerationalGeneticAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            combination_operator,
            std::get<int>(htg->hyperparameter_values["gga_population_size"]),
            std::get<int>(htg->hyperparameter_values["gga_evaluations"]),
            std::get<double>(htg->hyperparameter_values["gga_worst_unit_coef"])
        );
    }

    if (alg == "es") {
        return new EvolutionStrategy(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            combination_operator,
            std::get<int>(htg->hyperparameter_values["es_population_size"]),
            std::get<int>(htg->hyperparameter_values["es_evaluations"]),
            std::get<double>(htg->hyperparameter_values["es_new_units_per_generation_percentage"])
        );
    }

    if (alg == "sia") {
        return new SimpleImmunologicalAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            std::get<int>(htg->hyperparameter_values["sia_population_size"]),
            std::get<int>(htg->hyperparameter_values["sia_evaluations"]),
            std::get<int>(htg->hyperparameter_values["sia_number_of_clones"])
        );
    }

    if (alg == "clonalg") {
        return new ClonalSelectionAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            std::get<int>(htg->hyperparameter_values["clonalg_population_size"]),
            std::get<int>(htg->hyperparameter_values["clonalg_evaluations"]),
            std::get<double>(htg->hyperparameter_values["clonalg_beta"]),
            std::get<double>(htg->hyperparameter_values["clonalg_new_random_units_percentage"]),
            std::get<int>(htg->hyperparameter_values["clonalg_perturbations_per_worst_unit"])
        );
    }

    return nullptr;
}

