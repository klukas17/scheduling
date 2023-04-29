//
// Created by mihael on 29/04/23.
//

#include "GenotypeDeserializer.h"
#include "MachineNode.h"
#include "yaml-cpp/yaml.h"

GenotypeDeserializer::GenotypeDeserializer(Topology *topology) {
    this->topology = topology;
}

Individual *GenotypeDeserializer::deserialize(std::string path) {

    Individual* individual = new Individual(topology);
    MachineNode* node = (MachineNode*) individual->getRootNode();
    TopologyElement* topology_root_element = topology->getRootElement();

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node machine_node = doc["machine"];

    if (machine_node) {
        YAML::Node job_processing_order_node = machine_node["job_processing_order"];

        std::vector<long> job_order = job_processing_order_node.as<std::vector<long>>();

        for (long id : job_order)
            node->add_job(id);
    }

    else {
        // todo:error + group types
    }

    return individual;
}