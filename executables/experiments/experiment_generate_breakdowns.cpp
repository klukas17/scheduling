//
// Created by mihael on 5/22/24.
//

#include <string>

#include "BreakdownsGenerator.h"
#include "BreakdownsGeneratorSerializer.h"
#include "ExponentialDistribution.h"
#include "JobGeneratorParameters.h"
#include "JobSequenceGenerator.h"
#include "JobSequenceGeneratorSerializer.h"
#include "JobSpecificationsParser.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "MachineTypeMap.h"
#include "Topology.h"
#include "UniformRealDistributionGenerator.h"

int main() {
    std::string const dir = "../experiments/experiment_111/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    std::map<long, MachineBreakdownsGeneratorParameters*> machine_parameters;
    for (auto [machine_id, topology_element] : topology->getTopologyElementsMap()) {
        if (topology_element->getTopologyElementType() == MACHINE_TOPOLOGY_ELEMENT) {
            machine_parameters[machine_id] = new MachineBreakdownsGeneratorParameters(
                machine_id,
                50,
                new ExponentialDistribution(0.2),
                new ExponentialDistribution(1)
            );
        }
    }

    auto topology_parameters = new TopologyBreakdownsGeneratorParameters(machine_parameters);

    BreakdownsGenerator::generateBreakdowns(topology, topology_parameters);

    BreakdownsGeneratorSerializer::serializeTopology(dir + "machine_topologyxx.yaml", topology);
}
