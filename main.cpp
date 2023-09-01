#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "JobSpecificationsParser.h"
#include "JobSequenceParser.h"
#include "GenotypeDeserializer.h"
#include "GenotypeSerializer.h"
#include "Simulator.h"
#include "TopologyUtils.h"
#include "PathNodeUtils.h"
#include "set"
#include "filesystem"
#include "iostream"

void run_example(const std::string& dir) {

    std::cout << "Running " << dir << std::endl;

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");
    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
    TopologyUtils::logTopology(topology, dir + "output/topology.txt");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence.yaml", machine_type_map, job_type_map, topology);
    PathNodeUtils::logPathNodes(jobs, dir + "output/path_nodes.txt");

    Individual* individual = GenotypeDeserializer::deserialize(dir + "individual.yaml", topology);
    GenotypeSerializer::serialize(dir + "output/individual.yaml", individual);

    Simulator::simulate(individual, topology, jobs, true, dir + "simulator_logs.txt");
}

int main() {
    std::set<std::string> examples_sorted_by_name;
    for (const auto& entry : std::filesystem::directory_iterator("../examples/")) {
        if (entry.is_directory()) {
            examples_sorted_by_name.insert(entry.path().string() + "/");
        }
    }
    for (const auto& entry : examples_sorted_by_name) {
        run_example(entry);
    }
}