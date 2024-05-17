//
// Created by mihael on 5/9/24.
//

#include "BasicTopologyEnumerator.h"
#include "EndToStartTopologyEnumerator.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "filesystem"
#include "iostream"
#include "RandomFairTopologyEnumerator.h"
#include "RandomPathTopologyEnumerator.h"
#include "RandomTopologyEnumerator.h"
#include "StartToEndTopologyEnumerator.h"

int main() {
    std::string const dir = "../tests/test_07/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");
    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    // auto topology_enumerator = new BasicTopologyEnumerator(topology);
    // auto topology_enumerator = new StartToEndTopologyEnumerator(topology, 4);
    // auto topology_enumerator = new EndToStartTopologyEnumerator(topology, 37);
    // auto topology_enumerator = new RandomTopologyEnumerator(topology, 5);
    // auto topology_enumerator = new RandomFairTopologyEnumerator(topology, 5);
    auto topology_enumerator = new RandomPathTopologyEnumerator(topology, 0.5);

    for (int i = 0; i < 300; i++) {
        auto partition = topology_enumerator->getPartition();
        for (auto id : partition) {
            std::cout << id << " ";
        }
        std::cout << std::endl;
    }
}
