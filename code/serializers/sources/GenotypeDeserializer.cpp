//
// Created by mihael on 29/04/23.
//

#include "GenotypeDeserializer.h"
#include "MachineNode.h"
#include "SerialGroupNode.h"
#include "ParallelGroupNode.h"
#include "yaml-cpp/yaml.h"

GenotypeDeserializer::GenotypeDeserializer() = default;

Individual *GenotypeDeserializer::deserialize(const std::string& path, Topology* topology) {

    auto individual = new Individual(topology);
    YAML::Node doc = YAML::LoadFile(path);

    deserializeNode(doc, individual->getRootNode());

    return individual;
}

void GenotypeDeserializer::deserializeNode(const YAML::Node &node, GenotypeNode *genotype_node, bool pass_job_processing_order, const std::vector<long>& job_processing_order) {

    if (node["machine"]) {
        auto machine_node = (MachineNode*) genotype_node;
        YAML::Node job_processing_order_node = node["machine"]["job_processing_order"];
        if (pass_job_processing_order) {
            for (long id : job_processing_order) {
                machine_node->addJob(id);
            }
        }
        else if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                machine_node->addJob(id);
        }
    }

    else if (node["serial"]) {

        auto serial_group_node = (SerialGroupNode*) genotype_node;
        YAML::Node job_processing_order_node = node["serial"]["job_processing_order"];

        if (pass_job_processing_order) {
            for (long id : job_processing_order) {
                serial_group_node->addJob(id);
            }
        }

        else if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                serial_group_node->addJob(id);
        }

        YAML::Node body_node = node["serial"]["body"];
        auto serial_group_node_body = serial_group_node->getBody();
        auto serial_group_node_job_processing_order = serial_group_node->getJobProcessingOrder();

        if (body_node) {
            for (int i = 0; i < serial_group_node_body.size(); i++) {
                deserializeNode(body_node[i], serial_group_node_body[i], true, serial_group_node_job_processing_order);
            }
        }

        else {
            // todo:error
        }
    }

    else if (node["parallel"]) {

        auto parallel_group_node = (ParallelGroupNode*) genotype_node;
        YAML::Node job_processing_order_node = node["parallel"]["job_processing_order"];

        if (pass_job_processing_order) {
            for (long id : job_processing_order) {
                parallel_group_node->addJob(id);
            }
        }

        else if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                parallel_group_node->addJob(id);
        }

        YAML::Node body_node = node["parallel"]["body"];
        auto serial_group_node_body = parallel_group_node->getBody();
        auto serial_group_node_job_processing_order = parallel_group_node->getJobProcessingOrder();

        if (body_node) {
            for (int i = 0; i < serial_group_node_body.size(); i++) {
                deserializeNode(body_node[i], serial_group_node_body[i]);
            }
        }

        else {
            // todo:error
        }
    }

    else if (node["route"]) {

        auto route_group_node = (SerialGroupNode*) genotype_node;
        YAML::Node job_processing_order_node = node["route"]["job_processing_order"];

        if (pass_job_processing_order) {
            for (long id : job_processing_order) {
                route_group_node->addJob(id);
            }
        }

        else if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                route_group_node->addJob(id);
        }

        YAML::Node body_node = node["route"]["body"];
        auto serial_group_node_body = route_group_node->getBody();
        auto serial_group_node_job_processing_order = route_group_node->getJobProcessingOrder();

        if (body_node) {
            for (int i = 0; i < serial_group_node_body.size(); i++) {
                deserializeNode(body_node[i], serial_group_node_body[i]);
            }
        }

        else {
            // todo:error
        }

    }

    else {
        // todo:error
    }
}