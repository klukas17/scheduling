//
// Created by mihael on 6/5/24.
//

#include <iostream>

#include "DiscountedTotalWeightedCompletionTimeObjectiveFunction.h"
#include "EvolutionStrategy.h"
#include "Job.h"
#include "JobSequenceParser.h"
#include "JobSpecificationsParser.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "MachineTypeMap.h"
#include "MultiExpressionProgrammingCombinationOperator.h"
#include "MultiExpressionProgrammingCreationOperator.h"
#include "MultiExpressionProgrammingGenotypeBlueprint.h"
#include "MultiExpressionProgrammingPerturbationOperator.h"
#include "MultiExpressionProgrammingSerializationOperator.h"
#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity.h"
#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"
#include "OnlineSchedulingAlgorithmClusterPerturbationOperator.h"
#include "OnlineSchedulingAlgorithmClusterSerializationOperator.h"
#include "Population.h"
#include "RandomFairTopologyEnumerator.h"
#include "SchedulingEvaluationFunction.h"
#include "SchedulingMetaAlgorithm.h"
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

    int population_size = 50;
    // *****************************
    int number_of_instructions = 150;
    double perturbation_rate = 0.05;

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

    auto sub_blueprint = new MultiExpressionProgrammingGenotypeBlueprint(
        number_of_instructions,
        -1,
        1
    );
    auto sub_creation_operator = new MultiExpressionProgrammingCreationOperator(sub_blueprint);
    auto sub_combination_operator = new MultiExpressionProgrammingCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new MultiExpressionProgrammingPerturbationOperator(sub_blueprint, perturbation_rate);
    auto sub_serialization_operator = new MultiExpressionProgrammingSerializationOperator(sub_blueprint);

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

    auto topology_enumerator = new RandomFairTopologyEnumerator(topology, std::round(std::sqrt(machines_with_algorithms)));

    std::vector<double> results;

    for (int i = 0; i < 10; i++) {
        auto sub_algorithm_population = new Population(population_size);
        auto algorithm_population = new Population(1);

        auto sub_algorithm = new EvolutionStrategy(
            sub_evaluation_function,
            creation_operator,
            perturbation_operator,
            combination_operator,
            population_size,
            250,
            0.05
        );

        auto algorithm = new SchedulingMetaAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            combination_operator,
            topology_enumerator,
            sub_algorithm,
            sub_algorithm_population,
            200
        );

        algorithm->optimize(algorithm_population);

        auto unit = algorithm_population->getGenotype(0);
        std::cout << "Run " << i + 1 << "/10, score = " << unit->fitness_score << std::endl;
        std::cout << "Genotype:" << std::endl;
        for (auto line : serialization_operator->serialize(unit->genotype)) {
            std::cout << line << std::endl;
        }
        std::cout << std::endl;

        results.push_back(unit->fitness_score);

        delete sub_algorithm_population;
        delete algorithm_population;
        delete sub_algorithm;
        delete algorithm;
    }

    std::cout << "RESULTS:" << std::endl;
    for (auto result : results) {
        std::cout << result << std::endl;
    }
}
