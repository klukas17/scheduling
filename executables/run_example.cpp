//
// Created by mihael on 5/7/24.
//

#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "JobSpecificationsParser.h"
#include "JobSequenceParser.h"
#include "GenotypeDeserializer.h"
#include "GenotypeSerializer.h"
#include "Simulator.h"
#include "TopologyUtils.h"
#include "PathNodeUtils.h"
#include "PathTreeNodeUtils.h"
#include "filesystem"
#include "iostream"
#include "MakespanObjectiveFunction.h"
#include "OfflineScheduler.h"

int main() {

    std::string dir = "../examples/example_001/";

    try {
        std::cout << "Running " << dir << std::endl;

        MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

        JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
        machine_type_map->constructSetupAndBatchRules(job_type_map);

        Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
        TopologyUtils::logTopology(topology, dir + "output/topology.txt");

        std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence.yaml", machine_type_map, job_type_map, topology);
        PathNodeUtils::logPathNodes(jobs, dir + "output/path_nodes.txt");
        PathTreeNodeUtils::logPathTreeNodes(jobs, dir + "output/path_tree_nodes.txt");

        Individual* individual = GenotypeDeserializer::deserialize(dir + "individual.yaml", topology);
        GenotypeSerializer::serialize(dir + "output/individual.yaml", individual);

        auto simulator = new Simulator();
        auto const scheduler = new OfflineScheduler(individual);
        auto const statistics = simulator->simulate(scheduler, topology, jobs, true, dir + "output/simulator_logs.txt");
        auto objective_function = MakespanObjectiveFunction();
        std::cout << "OBJECTIVE FUNCTION: " << objective_function.evaluate(statistics) << std::endl;
    }
    catch (...) {
        std::cout << "FAILED" << std::endl;
    }
}