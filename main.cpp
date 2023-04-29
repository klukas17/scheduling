#include <iostream>
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "MachineType.h"
#include "Topology.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    MachineSpecificationsParser* machineSpecificationsParser = new MachineSpecificationsParser();
    std::map<long, MachineType*> machine_type_map = machineSpecificationsParser->parse("../examples/example_01/machine_specifications.yaml");

    MachineTopologyParser* machineTopologyParser = new MachineTopologyParser();
    Topology* topology = machineTopologyParser->parse("../examples/example_01/machine_topology.yaml", machine_type_map);

    return 0;
}