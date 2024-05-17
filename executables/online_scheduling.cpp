//
// Created by mihael on 5/5/24.
//

#include "BasicTopologyEnumerator.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "JobSpecificationsParser.h"
#include "JobSequenceParser.h"
#include "Simulator.h"
#include "TopologyUtils.h"
#include "filesystem"
#include "MakespanObjectiveFunction.h"
#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity.h"
#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"
#include "OnlineSchedulingAlgorithmClusterPerturbationOperator.h"
#include "RandomProgrammingCombinationOperator.h"
#include "RandomProgrammingCreationOperator.h"
#include "RandomProgrammingGenotypeBlueprint.h"
#include "RandomProgrammingPerturbationOperator.h"
#include "SchedulingEvaluationFunction.h"
#include "SchedulingMetaAlgorithm.h"
#include "SteadyStateGeneticAlgorithm.h"

int main() {
    std::string const dir = "../tests/test_02/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
    TopologyUtils::logTopology(topology, dir + "output/topology.txt");

    std::map<long, Job*> jobs_train_set = JobSequenceParser::parse(dir + "job_sequence_train.yaml", machine_type_map, job_type_map, topology);
    std::map<long, Job*> jobs_test_set = JobSequenceParser::parse(dir + "job_sequence_test.yaml", machine_type_map, job_type_map, topology);

    auto inner_algorithm_iteration_count = 10;
    auto meta_algorithm_iteration_count = 20;

    auto inner_algorithm_population_size = 10;
    auto meta_algorithm_population_size = 1;

    auto objective_function = new MakespanObjectiveFunction();
    auto inner_optimization_algorithm_evaluation_function = new SchedulingEvaluationFunction(
        objective_function,
        topology,
        jobs_train_set,
        true,
        dir + "output/train_logs/"
    );
    auto meta_optimization_algorithm_evaluation_function = new SchedulingEvaluationFunction(
        objective_function,
        topology,
        jobs_test_set,
        true,
        dir + "output/test_logs/"
    );

    auto online_scheduling_algorithm_genotype_blueprint = new RandomProgrammingGenotypeBlueprint(0, 1);
    auto online_scheduling_algorithm_creation_operator = new RandomProgrammingCreationOperator(online_scheduling_algorithm_genotype_blueprint);
    auto online_scheduling_algorithm_perturbation_operator = new RandomProgrammingPerturbationOperator();
    auto online_scheduling_algorithm_combination_operator = new RandomProgrammingCombinationOperator();

    auto online_scheduling_algorithm_cluster_genotype_blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto online_scheduling_algorithm_cluster_creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        online_scheduling_algorithm_cluster_genotype_blueprint,
        online_scheduling_algorithm_creation_operator
    );
    auto online_scheduling_algorithm_cluster_perturbation_operator = new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        online_scheduling_algorithm_perturbation_operator
    );
    auto online_scheduling_algorithm_cluster_combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        online_scheduling_algorithm_combination_operator
    );

    auto topology_enumerator = new BasicTopologyEnumerator(topology);

    auto inner_algorithm_population = new Population(inner_algorithm_population_size);
    auto meta_algorithm_population = new Population(meta_algorithm_population_size);

    auto inner_algorithm = new SteadyStateGeneticAlgorithm(
        inner_optimization_algorithm_evaluation_function,
        online_scheduling_algorithm_cluster_creation_operator,
        online_scheduling_algorithm_cluster_perturbation_operator,
        online_scheduling_algorithm_cluster_combination_operator,
        inner_algorithm_population_size,
        inner_algorithm_iteration_count
    );

    auto meta_algorithm = new SchedulingMetaAlgorithm(
        meta_optimization_algorithm_evaluation_function,
        online_scheduling_algorithm_cluster_creation_operator,
        online_scheduling_algorithm_cluster_perturbation_operator,
        online_scheduling_algorithm_cluster_combination_operator,
        topology_enumerator,
        inner_algorithm,
        inner_algorithm_population,
        meta_algorithm_iteration_count
    );
    meta_algorithm->optimize(meta_algorithm_population);
}
