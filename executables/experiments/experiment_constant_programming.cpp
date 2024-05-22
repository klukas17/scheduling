//
// Created by mihael on 5/22/24.
//

#include "BasicTopologyEnumerator.h"
#include "ConstantProgramming.h"
#include "ConstantProgrammingCombinationOperator.h"
#include "ConstantProgrammingCreationOperator.h"
#include "ConstantProgrammingGenotypeBlueprint.h"
#include "ConstantProgrammingPerturbationOperator.h"
#include "DiscountedTotalWeightedCompletionTimeObjectiveFunction.h"
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
#include "Population.h"
#include "SchedulingEvaluationFunction.h"
#include "SchedulingMetaAlgorithm.h"
#include "SteadyStateGeneticAlgorithm.h"

int main() {

    std::string const dir = "../experiments/experiment_05/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    std::map<long, Job*> jobs_train_set = JobSequenceParser::parse(dir + "job_sequence_train.yaml", machine_type_map, job_type_map, topology);
    std::map<long, Job*> jobs_test_set = JobSequenceParser::parse(dir + "job_sequence_test.yaml", machine_type_map, job_type_map, topology);

    auto sub_iteration_count = 50;
    auto iteration_count = 500;

    auto sub_population_size = 20;
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

    auto sub_genotype_blueprint = new ConstantProgrammingGenotypeBlueprint(0);
    auto sub_creation_operator = new ConstantProgrammingCreationOperator(sub_genotype_blueprint);
    auto sub_perturbation_operator = new ConstantProgrammingPerturbationOperator();
    auto sub_combination_operator = new ConstantProgrammingCombinationOperator();

    auto genotype_blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        genotype_blueprint,
        sub_creation_operator
    );
    auto perturbation_operator = new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto topology_enumerator = new BasicTopologyEnumerator(topology);

    auto sub_algorithm_population = new Population(sub_population_size);
    auto algorithm_population = new Population(population_size);

    auto sub_algorithm = new SteadyStateGeneticAlgorithm(
        sub_evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        sub_population_size,
        sub_iteration_count
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
}


