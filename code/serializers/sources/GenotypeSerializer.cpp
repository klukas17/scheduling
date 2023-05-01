//
// Created by mihael on 29/04/23.
//

#include "GenotypeSerializer.h"
#include "MachineNode.h"
#include "SerialGroupNode.h"
#include "ParallelGroupNode.h"
#include "RouteGroupNode.h"
#include "OpenGroupNode.h"
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

        case MACHINE_NODE_TYPE: {
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

        case SERIAL_GROUP_NODE_TYPE: {
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

        case PARALLEL_GROUP_NODE_TYPE: {
            auto parallel_group_node = (ParallelGroupNode*) node;
            out << YAML::BeginMap;
            out << YAML::Key << "parallel";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "job_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : parallel_group_node->getJobProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto body_node : parallel_group_node->getBody()) {
                serializeNode(body_node, out);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

        case ROUTE_GROUP_NODE_TYPE: {
            auto route_group_node = (RouteGroupNode*) node;
            out << YAML::BeginMap;
            out << YAML::Key << "route";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "job_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : route_group_node->getJobProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto body_node : route_group_node->getBody()) {
                serializeNode(body_node, out);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

        case OPEN_GROUP_NODE_TYPE: {
            auto open_group_node = (OpenGroupNode*) node;
            out << YAML::BeginMap;
            out << YAML::Key << "open";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "job_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : open_group_node->getJobProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto body_node : open_group_node->getBody()) {
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