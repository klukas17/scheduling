//
// Created by mihael on 6/3/24.
//

#include <iostream>

#include "HyperparameterTuningCombinationOperator.h"
#include "HyperparameterTuningCreationOperator.h"
#include "HyperparameterTuningEvaluationFunctionCGP.h"
#include "HyperparameterTuningGenotypeBlueprint.h"
#include "HyperparameterTuningPerturbationOperator.h"
#include "HyperparameterTuningSerializationOperator.h"
#include "Job.h"
#include "JobSequenceParser.h"
#include "JobSpecificationsParser.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "MachineTypeMap.h"
#include "Population.h"
#include "SteadyStateGeneticAlgorithm.h"
#include "Topology.h"

int main() {
    // data structures for the simulator
    std::string const dir = "../experiments/experiment_00/";
    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");
    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);
    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
    std::map<long, Job*> jobs_train_set = JobSequenceParser::parse(dir + "job_sequence_train.yaml", machine_type_map, job_type_map, topology);
    std::map<long, Job*> jobs_test_set = JobSequenceParser::parse(dir + "job_sequence_test.yaml", machine_type_map, job_type_map, topology);

    // hyperparameters for the hyperparameter-tuning algorithm (metahyperparameters)
    std::vector<std::string> hyperparameters;
    std::map<std::string, std::vector<hyperparameter_value>> hyperparameter_domains;
    double perturbation_rate = 0.2;
    int number_of_evaluations = 1000;
    int population_size = 10;
    int iterations = 200;

    hyperparameters = {
        "cluster_combination_operator_granularity",
        "topology_enumerator_scheme",
        "random_path_topology_enumerator_change_element_chance",
        "optimization_algorithm",
        "ssga_population_size",
        "ssga_evaluations",
        "gga_population_size",
        "gga_evaluations",
        "gga_worst_unit_coef",
        "es_population_size",
        "es_evaluations",
        "es_new_units_per_generation_percentage",
        "sia_population_size",
        "sia_evaluations",
        "sia_number_of_clones",
        "clonalg_population_size",
        "clonalg_evaluations",
        "clonalg_beta",
        "clonalg_new_random_units_percentage",
        "clonalg_perturbations_per_worst_unit",
        //**************************************************
        "cgp_rows",
        "cgp_cols",
        "cgp_perturbation_rate"
    };
    hyperparameter_domains["cluster_combination_operator_granularity"] = {"coarse", "fine"};
    hyperparameter_domains["topology_enumerator_scheme"] = {
        "all",
        "1,beginning",
        "1,end",
        "1,random_fair",
        "1,random_true",
        "k,beginning",
        "k,end",
        "k,random_fair",
        "k,random_true",
        "random_path"
    };
    hyperparameter_domains["random_path_topology_enumerator_change_element_chance"] = {0.5, 0.6, 0.7, 0.8, 0.9};
    hyperparameter_domains["optimization_algorithm"] = {"ssga", "gga", "es", "sia", "clonalg"};
    hyperparameter_domains["ssga_population_size"] = {5, 10, 15, 20};
    hyperparameter_domains["ssga_evaluations"] = {100, 50, 25, 20};
    hyperparameter_domains["gga_population_size"] = {5, 10, 15, 20};
    hyperparameter_domains["gga_evaluations"] = {100, 50, 25, 20};
    hyperparameter_domains["gga_worst_unit_coef"] = {0.1, 0.2, 0.3, 0.4, 0.5};
    hyperparameter_domains["es_population_size"] = {5, 10, 15, 20};
    hyperparameter_domains["es_evaluations"] = {100, 50, 25, 20};
    hyperparameter_domains["es_new_units_per_generation_percentage"] = {0.05, 0.1, 0.15, 0.2, 0.3, 0.4, 0.5};
    hyperparameter_domains["sia_population_size"] = {5, 10, 15, 20};
    hyperparameter_domains["sia_evaluations"] = {100, 50, 25, 20};
    hyperparameter_domains["sia_number_of_clones"] = {1, 2, 3, 4, 5};
    hyperparameter_domains["clonalg_population_size"] = {5, 10, 15, 20};
    hyperparameter_domains["clonalg_evaluations"] = {100, 50, 25, 20};
    hyperparameter_domains["clonalg_beta"] = {0.1, 0.2, 0.3, 0.4, 0.5};
    hyperparameter_domains["clonalg_new_random_units_percentage"] = {0.05, 0.1, 0.15, 0.2};
    hyperparameter_domains["clonalg_perturbations_per_worst_unit"] = {3, 5, 8, 10};
    // ********************************************************************************
    hyperparameter_domains["cgp_rows"] = {3, 5, 8, 10, 15};
    hyperparameter_domains["cgp_cols"] = {3, 5, 8, 10, 15};
    hyperparameter_domains["cgp_perturbation_rate"] = {0.05, 0.1, 0.2, 0.3};

    // operators for optimizing hyperparameters
    auto blueprint = new HyperparameterTuningGenotypeBlueprint(hyperparameters, hyperparameter_domains);
    auto creation_operator = new HyperparameterTuningCreationOperator(blueprint);
    auto combination_operator = new HyperparameterTuningCombinationOperator(blueprint);
    auto perturbation_operator = new HyperparameterTuningPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new HyperparameterTuningSerializationOperator(blueprint);

    // CHANGE FOR EACH ALGORITHM
    // evaluation function for optimizing hyperparameters
    auto evaluation_function = new HyperparameterTuningEvaluationFunctionCGP(
        topology,
        jobs_train_set,
        jobs_test_set,
        number_of_evaluations
    );

    // optimization
    auto population = new Population(population_size);
    auto algorithm = new SteadyStateGeneticAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        population_size,
        iterations
    );
    algorithm->optimize(population);
    auto solution = population->getGenotype(0)->genotype;
    std::cout << std::endl << "SOLUTION: " << std::endl;
    for (const auto& line : serialization_operator->serialize(solution)) {
        std::cout << line << std::endl;
    }
}
