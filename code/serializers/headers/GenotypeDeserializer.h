//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPEDESERIALIZER_H
#define SCHEDULING_GENOTYPEDESERIALIZER_H

#include "Topology.h"
#include "Individual.h"
#include "Job.h"
#include "string"
#include "yaml-cpp/yaml.h"

class GenotypeDeserializer {
public:
    explicit GenotypeDeserializer();
    static Individual* deserialize(const std::string& path, Topology* topology, const std::map<long, Job*>& jobs);
    static void deserializeTopologyNode(const YAML::Node& node, GenotypeNode* genotype_node);
    static void deserializeJobsNode(const YAML::Node& node, Individual* individual, const std::map<long, Job*>& jobs);
};


#endif //SCHEDULING_GENOTYPEDESERIALIZER_H
