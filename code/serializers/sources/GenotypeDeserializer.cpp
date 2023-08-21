//
// Created by mihael on 29/04/23.
//

/**
 * @file GenotypeDeserializer.cpp
 * @brief Implements the member functions of the GenotypeDeserializer class.
 */

#include "GenotypeDeserializer.h"
#include "MachineNode.h"
#include "SerialGroupNode.h"
#include "ParallelGroupNode.h"
#include "RouteGroupNode.h"
#include "OpenGroupNode.h"
#include "JobProcessingRoute.h"
#include "JobProcessingStep.h"
#include "SchedulingError.h"
#include "yaml-cpp/yaml.h"

Individual *GenotypeDeserializer::deserialize(const std::string& path, Topology* topology) {

    auto individual = new Individual(topology);
    YAML::Node doc = YAML::LoadFile(path);

    if (!doc["topology"]) {
        throw SchedulingError("'topology' node not found in " + path);
    }

    if (!doc["jobs"]) {
        throw SchedulingError("'jobs' node not found in " + path);
    }

    deserializeTopologyNode(path, doc["topology"], individual->getRootNode());
    deserializeJobsNode(path, doc["jobs"], individual);

    return individual;
}

void GenotypeDeserializer::deserializeTopologyNode(const std::string& path, const YAML::Node &node, GenotypeNode *genotype_node) {

    if (node["machine"]) {
        auto machine_node = (MachineNode*) genotype_node;
        if (!node["machine"]["step_processing_order"]) {
            throw SchedulingError("'machine' node without 'step_processing_order' child node found in " + path);
        }
        YAML::Node job_processing_order_node = node["machine"]["step_processing_order"];

        auto job_order = job_processing_order_node.as<std::vector<long>>();
        for (long id : job_order) {
            machine_node->addStep(id);
        }
    }

    else if (node["serial"]) {

        auto serial_group_node = (SerialGroupNode*) genotype_node;

        if (!node["serial"]["step_processing_order"]) {
            throw SchedulingError("'serial' node without 'step_processing_order' child node found in " + path);
        }
        if (!node["serial"]["body"]) {
            throw SchedulingError("'serial' node without 'body' child node found in " + path);
        }

        YAML::Node job_processing_order_node = node["serial"]["step_processing_order"];
        auto job_order = job_processing_order_node.as<std::vector<long>>();
        for (long id : job_order) {
            serial_group_node->addStep(id);
        }

        YAML::Node body_node = node["serial"]["body"];
        auto serial_group_node_body = serial_group_node->getBody();
        auto serial_group_node_job_processing_order = serial_group_node->getStepProcessingOrder();
        for (int i = 0; i < serial_group_node_body.size(); i++) {
            deserializeTopologyNode(path, body_node[i], serial_group_node_body[i]);
        }
    }

    else if (node["parallel"]) {

        auto parallel_group_node = (ParallelGroupNode*) genotype_node;

        if (!node["parallel"]["step_processing_order"]) {
            throw SchedulingError("'parallel' node without 'step_processing_order' child node found in " + path);
        }
        if (!node["parallel"]["body"]) {
            throw SchedulingError("'parallel' node without 'body' child node found in " + path);
        }

        YAML::Node job_processing_order_node = node["parallel"]["step_processing_order"];
        auto job_order = job_processing_order_node.as<std::vector<long>>();
        for (long id : job_order) {
            parallel_group_node->addStep(id);
        }

        YAML::Node body_node = node["parallel"]["body"];
        auto parallel_group_node_body = parallel_group_node->getBody();
        for (int i = 0; i < parallel_group_node_body.size(); i++) {
            deserializeTopologyNode(path, body_node[i], parallel_group_node_body[i]);
        }
    }

    else if (node["route"]) {

        auto route_group_node = (RouteGroupNode*) genotype_node;

        if (!node["route"]["step_processing_order"]) {
            throw SchedulingError("'route' node without 'step_processing_order' child node found in " + path);
        }
        if (!node["route"]["body"]) {
            throw SchedulingError("'route' node without 'body' child node found in " + path);
        }

        YAML::Node job_processing_order_node = node["route"]["step_processing_order"];
        auto job_order = job_processing_order_node.as<std::vector<long>>();
        for (long id : job_order) {
            route_group_node->addStep(id);
        }

        YAML::Node body_node = node["route"]["body"];
        auto route_group_node_body = route_group_node->getBody();
        for (int i = 0; i < route_group_node_body.size(); i++) {
            deserializeTopologyNode(path, body_node[i], route_group_node_body[i]);
        }
    }

    else if (node["open"]) {

        auto open_group_node = (OpenGroupNode*) genotype_node;

        if (!node["open"]["step_processing_order"]) {
            throw SchedulingError("'open' node without 'step_processing_order' child node found in " + path);
        }
        if (!node["open"]["body"]) {
            throw SchedulingError("'open' node without 'body' child node found in " + path);
        }

        YAML::Node job_processing_order_node = node["open"]["step_processing_order"];
        auto job_order = job_processing_order_node.as<std::vector<long>>();
        for (long id : job_order) {
            open_group_node->addStep(id);
        }

        YAML::Node body_node = node["open"]["body"];
        auto open_group_node_body = open_group_node->getBody();
        for (int i = 0; i < open_group_node_body.size(); i++) {
            deserializeTopologyNode(path, body_node[i], open_group_node_body[i]);
        }
    }

    else {
        throw SchedulingError("Topology node must be of type [machine, serial, parallel, route, open] in " + path);
    }
}

void GenotypeDeserializer::deserializeJobsNode(const std::string& path, const YAML::Node &node, Individual *individual) {

    for (YAML::const_iterator it = node.begin(); it != node.end(); it++) {
        if (!(*it)["job_id"]) {
            throw SchedulingError("'job' node without 'job_id' child node found in " + path);
        }
        long job_id = (*it)["job_id"].as<long>();
        if (!(*it)["processing_route"]) {
            throw SchedulingError("'job' node without 'processing_route' child node found in " + path);
        }
        const YAML::Node processing_route_node = (*it)["processing_route"];
        auto job_processing_route = new JobProcessingRoute(job_id);
        for (YAML::const_iterator it_route = processing_route_node.begin(); it_route != processing_route_node.end(); it_route++) {
            if (!(*it_route)["machine_id"]) {
                throw SchedulingError("'job' node without 'machine_id' child node found in " + path);
            }
            long machine_id = (*it_route)["machine_id"].as<long>();
            if (!(*it_route)["processing_step_id"]) {
                throw SchedulingError("'job' node without 'processing_step_id' child node found in " + path);
            }
            long processing_step_id = (*it_route)["processing_step_id"].as<long>();
            auto job_processing_step = new JobProcessingStep(processing_step_id, machine_id, job_id);
            job_processing_route->addProcessingStep(job_processing_step);
        }
        individual->setProcessingRoute(job_id, job_processing_route);
    }
}