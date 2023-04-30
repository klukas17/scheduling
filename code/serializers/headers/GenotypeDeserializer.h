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
private:
public:
    explicit GenotypeDeserializer();
    static Individual* deserialize(const std::string& path, Topology* topology);
    static void deserializeNode(const YAML::Node& node, GenotypeNode* genotype_node, bool pass_job_processing_order = false, const std::vector<long>& job_processing_order = std::vector<long>());
};


#endif //SCHEDULING_GENOTYPEDESERIALIZER_H
