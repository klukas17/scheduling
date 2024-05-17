//
// Created by mihael on 5/8/24.
//

#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "JobSpecificationsParser.h"
#include "JobSequenceParser.h"
#include "Simulator.h"
#include "TopologyUtils.h"
#include "filesystem"
#include "MakespanObjectiveFunction.h"
#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"
#include "RandomProgrammingCreationOperator.h"
#include "RandomProgrammingGenotypeBlueprint.h"
#include "SchedulingEvaluationFunction.h"
#include "SteadyStateGeneticAlgorithm.h"

int main() {

    std::string const dir = "../tests/test_11/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
    TopologyUtils::logTopology(topology, dir + "output/topology.txt");

    std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence_train.yaml", machine_type_map, job_type_map, topology);

    auto objective_function = new MakespanObjectiveFunction();
    auto evaluation_function = new SchedulingEvaluationFunction(
        objective_function,
        topology,
        jobs,
        true,
        dir + "output/"
    );

    auto online_scheduling_algorithm_genotype_blueprint = new RandomProgrammingGenotypeBlueprint(0, 1);
    auto online_scheduling_algorithm_creation_operator = new RandomProgrammingCreationOperator(online_scheduling_algorithm_genotype_blueprint);
    auto online_scheduling_algorithm_cluster_genotype_blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto online_scheduling_algorithm_cluster_creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        online_scheduling_algorithm_cluster_genotype_blueprint,
        online_scheduling_algorithm_creation_operator
    );

    auto genotype = online_scheduling_algorithm_cluster_creation_operator->create();
    evaluation_function->evaluate(genotype);
}