//
// Created by mihael on 29/04/23.
//

#include "GenotypeDeserializer.h"
#include "MachineNode.h"
#include "SerialGroupNode.h"
#include "ParallelGroupNode.h"
#include "RouteGroupNode.h"
#include "OpenGroupNode.h"
#include "JobProcessingRoute.h"
#include "JobProcessingStep.h"
#include "yaml-cpp/yaml.h"

GenotypeDeserializer::GenotypeDeserializer() = default;

Individual *GenotypeDeserializer::deserialize(const std::string& path, Topology* topology) {

    auto individual = new Individual(topology);
    YAML::Node doc = YAML::LoadFile(path);

    deserializeTopologyNode(doc["topology"], individual->getRootNode());
    deserializeJobsNode(doc["jobs"], individual);

    return individual;
}

void GenotypeDeserializer::deserializeTopologyNode(const YAML::Node &node, GenotypeNode *genotype_node) {

    if (node["machine"]) {
        auto machine_node = (MachineNode*) genotype_node;
        YAML::Node job_processing_order_node = node["machine"]["step_processing_order"];

        if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                machine_node->addStep(id);
        }
    }

    else if (node["serial"]) {

        auto serial_group_node = (SerialGroupNode*) genotype_node;
        YAML::Node job_processing_order_node = node["serial"]["step_processing_order"];

        if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                serial_group_node->addStep(id);
        }

        YAML::Node body_node = node["serial"]["body"];
        auto serial_group_node_body = serial_group_node->getBody();
        auto serial_group_node_job_processing_order = serial_group_node->getStepProcessingOrder();

        if (body_node) {
            for (int i = 0; i < serial_group_node_body.size(); i++) {
                deserializeTopologyNode(body_node[i], serial_group_node_body[i]);
            }
        }

        else {
            // todo:error
        }
    }

    else if (node["parallel"]) {

        auto parallel_group_node = (ParallelGroupNode*) genotype_node;
        YAML::Node job_processing_order_node = node["parallel"]["step_processing_order"];

        if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                parallel_group_node->addStep(id);
        }

        YAML::Node body_node = node["parallel"]["body"];
        auto parallel_group_node_body = parallel_group_node->getBody();

        if (body_node) {
            for (int i = 0; i < parallel_group_node_body.size(); i++) {
                deserializeTopologyNode(body_node[i], parallel_group_node_body[i]);
            }
        }

        else {
            // todo:error
        }
    }

    else if (node["route"]) {

        auto route_group_node = (RouteGroupNode*) genotype_node;
        YAML::Node job_processing_order_node = node["route"]["step_processing_order"];

        if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                route_group_node->addStep(id);
        }

        YAML::Node body_node = node["route"]["body"];
        auto route_group_node_body = route_group_node->getBody();

        if (body_node) {
            for (int i = 0; i < route_group_node_body.size(); i++) {
                deserializeTopologyNode(body_node[i], route_group_node_body[i]);
            }
        }

        else {
            // todo:error
        }

    }

    else if (node["open"]) {

        auto open_group_node = (OpenGroupNode*) genotype_node;
        YAML::Node job_processing_order_node = node["open"]["step_processing_order"];

        if (job_processing_order_node) {
            auto job_order = job_processing_order_node.as<std::vector<long>>();
            for (long id : job_order)
                open_group_node->addStep(id);
        }

        YAML::Node body_node = node["open"]["body"];
        auto open_group_node_body = open_group_node->getBody();

        if (body_node) {
            for (int i = 0; i < open_group_node_body.size(); i++) {
                deserializeTopologyNode(body_node[i], open_group_node_body[i]);
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

void GenotypeDeserializer::deserializeJobsNode(const YAML::Node &node, Individual *individual) {

    if (node) {
        for (YAML::const_iterator it = node.begin(); it != node.end(); it++) {
            long id = (*it)["job_id"].as<long>();
            const YAML::Node processing_route_node = (*it)["processing_route"];
            if (processing_route_node) {
                auto job_processing_route = new JobProcessingRoute(id);
                for (YAML::const_iterator it_route = processing_route_node.begin(); it_route != processing_route_node.end(); it_route++) {
                    long machine_id = (*it_route)["machine_id"].as<long>();
                    long processing_step_id = (*it_route)["processing_step_id"].as<long>();
                    auto job_processing_step = new JobProcessingStep(processing_step_id, machine_id);
                    job_processing_route->addProcessingStep(job_processing_step);
                }
                individual->setProcessingRoute(id, job_processing_route);
            }
            else {
                // todo:error
            }
        }
    }

    else {
        // todo:error
    }
}