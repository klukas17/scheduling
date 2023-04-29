#include <iostream>
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "JobSpecificationsParser.h"
#include "MachineType.h"
#include "Topology.h"

std::string dir = "../examples/example_01/";

int main() {
    std::cout << "Hello, World!" << std::endl;

    MachineSpecificationsParser* machineSpecificationsParser = new MachineSpecificationsParser();
    std::map<long, MachineType*> machine_type_map = machineSpecificationsParser->parse(dir + "machine_specifications.yaml");

    MachineTopologyParser* machineTopologyParser = new MachineTopologyParser();
    Topology* topology = machineTopologyParser->parse(dir + "machine_topology.yaml", machine_type_map);

    JobSpecificationsParser* jobSpecificationsParser = new JobSpecificationsParser();
    std::map<long, JobType*> job_type_map = jobSpecificationsParser->parse(dir + "job_specifications.yaml");

    return 0;
}