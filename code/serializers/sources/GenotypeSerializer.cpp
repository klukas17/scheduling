//
// Created by mihael on 29/04/23.
//

#include "GenotypeSerializer.h"
#include "MachineNode.h"
#include "SerialGroupNode.h"
#include "fstream"

GenotypeSerializer::GenotypeSerializer() = default;

void GenotypeSerializer::serialize(const std::string& path, Individual *individual) {
    YAML::Emitter out;
    serializeNode(individual->getRootNode(), out);
    std::ofstream file(path);
    file << out.c_str();
    file.close();
}

void GenotypeSerializer::serializeNode(GenotypeNode *node, YAML::Emitter& out) {

    switch (node->getNodeType()) {

        case MACHINE_NODE_TYPE : {
            auto machine_node = (MachineNode*) node;
            out << YAML::BeginMap;
            out << YAML::Key << "machine";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "job_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : machine_node->getJobProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

        case SERIAL_GROUP_NODE_TYPE : {
            auto serial_group_node = (SerialGroupNode*) node;
            out << YAML::BeginMap;
            out << YAML::Key << "serial";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "job_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : serial_group_node->getJobProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto body_node : serial_group_node->getBody()) {
                serializeNode(body_node, out);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

        default: {
            // todo:error
            break;
        }

    }
}