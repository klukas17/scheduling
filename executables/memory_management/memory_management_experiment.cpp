//
// Created by mihael on 6/3/24.
//

#include <iostream>

#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "JobSpecificationsParser.h"
#include "JobSequenceParser.h"
#include "Simulator.h"
#include "filesystem"
#include "OnlineScheduler.h"
#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"
#include "Population.h"
#include "RandomProgrammingCreationOperator.h"
#include "RandomProgrammingGenotypeBlueprint.h"
#include "SchedulingEvaluationFunction.h"

int main() {
    std::string const dir = "../experiments/experiment_05/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence_train.yaml", machine_type_map, job_type_map, topology);

    auto sub_blueprint = new RandomProgrammingGenotypeBlueprint(0, 1);
    auto sub_creation_operator = new RandomProgrammingCreationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto cluster = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    for (int i = 0; i < 1000000000; i++) {
        std::cout << i << std::endl;

        auto scheduler = new OnlineScheduler(cluster);
        auto simulator = new Simulator();
        scheduler->intializeJobContexts(jobs);
        auto simulator_statistics = simulator->simulate(scheduler, topology, jobs, false, "");

        delete scheduler;
        delete simulator;
        delete simulator_statistics;
    }
}