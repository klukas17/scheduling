//
// Created by mihael on 6/5/24.
//

#include <iostream>

#include "DiscountedTotalWeightedCompletionTimeObjectiveFunction.h"
#include "Job.h"
#include "JobSequenceParser.h"
#include "JobSpecificationsParser.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "MachineTypeMap.h"
#include "NeuralNetworkCombinationOperator.h"
#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"
#include "NeuralNetworkPerturbationOperator.h"
#include "NeuralNetworkSerializationOperator.h"
#include "NormalDistribution.h"
#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity.h"
#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"
#include "OnlineSchedulingAlgorithmClusterPerturbationOperator.h"
#include "OnlineSchedulingAlgorithmClusterSerializationOperator.h"
#include "Population.h"
#include "RandomTopologyEnumerator.h"
#include "SchedulingEvaluationFunction.h"
#include "SchedulingMetaAlgorithm.h"
#include "SimpleImmunologicalAlgorithm.h"
#include "Topology.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <string_argument>" << std::endl;
        return 1;
    }

    std::string dir = argv[1];

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");
    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);
    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
    std::map<long, Job*> jobs_train_set = JobSequenceParser::parse(dir + "job_sequence_train.yaml", machine_type_map, job_type_map, topology);
    std::map<long, Job*> jobs_test_set = JobSequenceParser::parse(dir + "job_sequence_test.yaml", machine_type_map, job_type_map, topology);

    int population_size = 150;
    // *******************
    double creation_sigma = 0.001;
    double perturbation_sigma = 0.01;
    std::string activation_function_name = "sigm";
    std::vector<int> layer_sizes = {5, 1};

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

    auto sub_blueprint = new NeuralNetworkGenotypeBlueprint(
        new NormalDistribution(0, creation_sigma),
        layer_sizes,
        activation_function_name
    );
    auto sub_creation_operator = new NeuralNetworkCreationOperator(sub_blueprint);
    auto sub_combination_operator = new NeuralNetworkCombinationOperator();
    auto sub_perturbation_operator = new NeuralNetworkPerturbationOperator(
        new NormalDistribution(0, perturbation_sigma)
    );
    auto sub_serialization_operator = new NeuralNetworkSerializationOperator(sub_blueprint);

    auto genotype_blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        genotype_blueprint,
        sub_creation_operator
    );
    auto perturbation_operator = new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity(
        sub_combination_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(
        topology,
        sub_serialization_operator
    );

    int machines_with_algorithms = 0;
    for (auto [element_id, element] : topology->getTopologyElementsMap()) {
        auto element_type = element->getTopologyElementType();
        if (element_type == MACHINE_TOPOLOGY_ELEMENT || element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT || element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
            machines_with_algorithms++;
        }
    }

    auto topology_enumerator = new RandomTopologyEnumerator(topology, std::round(std::sqrt(machines_with_algorithms)));

    std::vector<double> results;

    auto sub_algorithm_population = new Population(population_size);
    auto algorithm_population = new Population(1);

    auto sub_algorithm = new SimpleImmunologicalAlgorithm(
        sub_evaluation_function,
        creation_operator,
        perturbation_operator,
        population_size,
        100,
        5
    );

    auto algorithm = new SchedulingMetaAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        topology_enumerator,
        sub_algorithm,
        sub_algorithm_population,
        500
    );

    algorithm->optimize(algorithm_population);

    auto unit = algorithm_population->getGenotype(0);
    std::cout << "Genotype:" << std::endl;
    for (auto line : serialization_operator->serialize(unit->genotype)) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
    std::cout << "RESULT: " << unit->fitness_score << std::endl;

    delete sub_algorithm_population;
    delete algorithm_population;
    delete sub_algorithm;
    delete algorithm;
}
