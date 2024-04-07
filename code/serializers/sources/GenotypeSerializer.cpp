//
// Created by mihael on 29/04/23.
//

#include "GenotypeSerializer.h"
#include "MachineNode.h"
#include "SerialGroupNode.h"
#include "ParallelGroupNode.h"
#include "RouteGroupNode.h"
#include "OpenGroupNode.h"
#include "SchedulingError.h"
#include "fstream"

void GenotypeSerializer::serialize(const std::string& path, Individual *individual) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    serializeTopologyNode(individual, out);
    serializeJobsNode(individual, out);
    out << YAML::EndMap;
    std::ofstream file(path);
    file << out.c_str();
    file.close();
}

void GenotypeSerializer::serializeTopologyNode(const Individual *individual, YAML::Emitter &out) {
    out << YAML::Key << "topology";
    serializeTopologyElementNode(individual->getRootNode(), out);
}

void GenotypeSerializer::serializeJobsNode(Individual *individual, YAML::Emitter &out) {
    out << YAML::Key << "jobs";
    out << YAML::Value << YAML::BeginSeq;
    for (const auto [job_id, job_processing_route] : individual->getProcessingRoutes()) {
        out << YAML::BeginMap << YAML::Flow;
        out << YAML::Key << "job_id";
        out << YAML::Value << job_id;
        out << YAML::Key << "processing_route";
        out << YAML::Value << YAML::BeginSeq;
        for (auto const entry : job_processing_route->getProcessingSteps()) {
            out << YAML::BeginMap;
            out << YAML::Key << "machine_id";
            out << YAML::Value << entry->getMachineId();
            out << YAML::Key << "path_node_id";
            out << YAML::Value << entry->getPathNodeId();
            out << YAML::Key << "processing_step_id";
            out << YAML::Value << entry->getProcessingStepId();
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
}


void GenotypeSerializer::serializeTopologyElementNode(GenotypeNode *node, YAML::Emitter& out) {

    switch (node->getNodeType()) {

        case ABSTRACT_NODE:
            throw SchedulingError("Abstract node encountered in GenotypeSerializer::serializeTopologyElementNode function.");

        case MACHINE_NODE: {
            auto const machine_node = dynamic_cast<MachineNode*>(node);
            out << YAML::BeginMap;
            out << YAML::Key << "machine";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "step_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : machine_node->getStepProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

        case SERIAL_GROUP_NODE: {
            auto const  serial_group_node = dynamic_cast<SerialGroupNode*>(node);
            out << YAML::BeginMap;
            out << YAML::Key << "serial";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "step_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : serial_group_node->getStepProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto const body_node : serial_group_node->getBody()) {
                serializeTopologyElementNode(body_node, out);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

        case PARALLEL_GROUP_NODE: {
            auto const parallel_group_node = dynamic_cast<ParallelGroupNode*>(node);
            out << YAML::BeginMap;
            out << YAML::Key << "parallel";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "step_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : parallel_group_node->getStepProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto const body_node : parallel_group_node->getBody()) {
                serializeTopologyElementNode(body_node, out);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

        case ROUTE_GROUP_NODE: {
            auto const route_group_node = dynamic_cast<RouteGroupNode*>(node);
            out << YAML::BeginMap;
            out << YAML::Key << "route";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "step_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : route_group_node->getStepProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto const body_node : route_group_node->getBody()) {
                serializeTopologyElementNode(body_node, out);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }

        case OPEN_GROUP_NODE: {
            auto const open_group_node = dynamic_cast<OpenGroupNode*>(node);
            out << YAML::BeginMap;
            out << YAML::Key << "open";
            out << YAML::Value << YAML::BeginMap;
            out << YAML::Key << "step_processing_order";
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& job : open_group_node->getStepProcessingOrder()) {
                out << job;
            }
            out << YAML::EndSeq;
            out << YAML::Key << "body";
            out << YAML::Value << YAML::BeginSeq;
            for (auto const body_node : open_group_node->getBody()) {
                serializeTopologyElementNode(body_node, out);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
            out << YAML::EndMap;
            break;
        }
    }
}