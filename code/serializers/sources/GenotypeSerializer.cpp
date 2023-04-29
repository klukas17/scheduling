//
// Created by mihael on 29/04/23.
//

#include "GenotypeSerializer.h"
#include "MachineNode.h"
#include <yaml-cpp/yaml.h>
#include "fstream"

GenotypeSerializer::GenotypeSerializer() {}

void GenotypeSerializer::serialize(std::string path, Individual *individual) {

    MachineNode* node = (MachineNode*) individual->getRootNode();

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "machine";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "job_processing_order";
    out << YAML::Value << YAML::BeginSeq;
    for (const auto& job : node->getJobProcessingOrder()) {
        out << job;
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;
    out << YAML::EndMap;

    std::ofstream file(path);
    file << out.c_str();
}