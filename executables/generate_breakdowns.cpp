//
// Created by mihael on 5/18/24.
//

#include "BitSumGenotype.h"
#include "BitSumPerturbationOperator.h"
#include "BreakdownsGenerator.h"
#include "BreakdownsGeneratorSerializer.h"
#include "ExponentialDistribution.h"
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
#include "set"
#include "filesystem"
#include "iostream"
#include "JobSequenceGenerator.h"
#include "JobSequenceGeneratorSerializer.h"
#include "MachineBreakdownsGeneratorParameters.h"
#include "MakespanObjectiveFunction.h"
#include "OfflineScheduler.h"
#include "TopologyBreakdownsGeneratorParameters.h"

int main() {
    std::set<std::string> examples_sorted_by_name;
    for (const auto& entry : std::filesystem::directory_iterator("../examples/")) {
        if (entry.is_directory()) {
            examples_sorted_by_name.insert(entry.path().string() + "/");
        }
    }
    for (const auto& dir : examples_sorted_by_name) {
        try {

            std::cout << "Running " << dir << std::endl;

            MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

            JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
            machine_type_map->constructSetupAndBatchRules(job_type_map);

            Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

            std::map<long, MachineBreakdownsGeneratorParameters*> machine_parameters;
            for (auto [machine_id, topology_element] : topology->getTopologyElementsMap()) {
                if (topology_element->getTopologyElementType() == MACHINE_TOPOLOGY_ELEMENT) {
                    machine_parameters[machine_id] = new MachineBreakdownsGeneratorParameters(
                        machine_id,
                        10,
                        new ExponentialDistribution(0.2),
                        new ExponentialDistribution(1)
                    );
                }
            }

            auto topology_parameters = new TopologyBreakdownsGeneratorParameters(machine_parameters);

            BreakdownsGenerator::generateBreakdowns(topology, topology_parameters);

            BreakdownsGeneratorSerializer::serializeTopology(dir + "output/machine_topology.yaml", topology);
            MachineTopologyParser::parse(dir + "output/machine_topology.yaml", machine_type_map);

        }
        catch (...) {
            std::cout << "FAILED" << std::endl;
        }
    }
}
