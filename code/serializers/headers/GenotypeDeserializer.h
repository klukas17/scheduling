//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPEDESERIALIZER_H
#define SCHEDULING_GENOTYPEDESERIALIZER_H

#include "Topology.h"
#include "Individual.h"
#include "string"
#include "yaml-cpp/yaml.h"

class GenotypeDeserializer {
public:
    static Individual* deserialize(const std::string& path, const Topology* topology);
    static void deserializeTopologyNode(const std::string& path, const YAML::Node& node, GenotypeNode* genotype_node);
    static void deserializeJobsNode(const std::string& path, const YAML::Node& node, Individual* individual);
};

#endif //SCHEDULING_GENOTYPEDESERIALIZER_H

