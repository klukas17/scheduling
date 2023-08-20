//
// Created by mihael on 29/04/23.
//

/**
 * @file JobSequenceParser.cpp
 * @brief Implements the member functions of the JobSequenceParser class.
 */

#include "JobSequenceParser.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "OpenGroupPathNode.h"
#include "MachineJobPathNode.h"
#include "SerialGroupJobPathNode.h"
#include "ParallelGroupJobPathNode.h"
#include "RouteGroupJobPathNode.h"
#include "OpenGroupJobPathNode.h"
#include "SerialGroup.h"
#include "yaml-cpp/yaml.h"

std::map<long, Job *> JobSequenceParser::parse(const std::string& path, JobTypeMap* job_type_map, Topology* topology) {

    std::map<long, Job*> jobs;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node job_sequence_node = doc["job_sequence"];

    if (job_sequence_node) {
        for (YAML::const_iterator it = job_sequence_node.begin(); it != job_sequence_node.end(); it++) {
            if (!(*it)["job_id"]) {
                throw SchedulingError("Entry in the 'job_sequence' array must contain 'job_id' field in the file " + path);
            }
            long id = (*it)["job_id"].as<long>();
            if (!(*it)["job_type_id"]) {
                throw SchedulingError("Entry in the 'job_sequence' array must contain 'job_type_id' field in the file " + path);
            }
            long job_type_id = (*it)["job_type_id"].as<long>();
            JobType* job_type = job_type_map->getJobType(job_type_id);
            long release_time = ((*it)["release_time"]) ? (*it)["release_time"].as<long>() : 0;
            long due_time = ((*it)["due_time"]) ? (*it)["due_time"].as<long>() : release_time;
            long weight = ((*it)["weight"]) ? (*it)["weight"].as<long>() : 1;

            JobPathNode* paths_root_node = nullptr;
            const YAML::Node& processing_route_node = (*it)["processing_route"];
            if (processing_route_node) {
                if (processing_route_node.size() != 1) {
                    throw SchedulingError("'processing_route' node for job with id " + std::to_string(id) + " can have only one child in " + path + " file.");
                }
                paths_root_node = parsePathNodeWithYAMLNode(*processing_route_node.begin(), path,
                    {{topology->getRootElement()->getId(), topology->getRootPathNode()}});
            }
            else {
                throw SchedulingError("'processing_route' node for job with id " + std::to_string(id) + " not found in " + path + " file.");
            }

            Job* job = new Job(id, job_type, paths_root_node, release_time, due_time, weight);
            jobs[id] = job;
        }
    }

    else {
        throw SchedulingError("'job_sequence' node not found in " + path + " file.");
    }

    return jobs;
}

JobPathNode *JobSequenceParser::parsePathNodeWithYAMLNode(const YAML::Node &node, const std::string& path, std::map<long, PathNode*> legal_path_nodes) {
    if (!node["machine_id"]) {
        throw SchedulingError("Entry in the 'topology' or 'sub_machines' arrays must contain 'machine_id' field in the file " + path);
    }
    long machine_id = node["machine_id"].as<long>();

    auto path_node = legal_path_nodes.find(machine_id)->second;

    if (path_node == nullptr) {
        throw SchedulingError("Entry in the 'sub_machines' array contains invalid 'machine_id' value of " + std::to_string(machine_id)  + " in the file " + path);
    }

    JobPathNode* job_path_node = nullptr;

    auto path_node_topology_element_type = path_node->getTopologyElement()->getTopologyElementType();

    if (path_node_topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in the file " + path);
    }

    else if (path_node_topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_job_path_node =  new MachineJobPathNode(path_node);
        job_path_node = machine_job_path_node;
        const YAML::Node& sub_machines_node = node["sub_machines"];
        if (sub_machines_node) {
            throw SchedulingError("Machine topology element of id " + std::to_string(machine_id) +  " cannot have sub_machines in the file " + path);
        }
    }

    else if (path_node_topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto serial_group_job_path_node = new SerialGroupJobPathNode(path_node);
        job_path_node = serial_group_job_path_node;

        const YAML::Node& sub_machines_node = node["sub_machines"];

        if (sub_machines_node) {
            std::vector<JobPathNode*> job_sub_path_nodes;
            auto serial_group_children_path_nodes = ((SerialGroupPathNode*)serial_group_job_path_node->getPathNode())->getChildren();
            long serial_group_children_index = 0;
            for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                long sub_machine_id = (*sub_machine_it)["machine_id"].as<long>();
                if (sub_machine_id != serial_group_children_path_nodes[serial_group_children_index]->getTopologyElement()->getId()) {
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                        ", expected 'machine_id' to be equal to " + std::to_string(serial_group_children_path_nodes[serial_group_children_index]->getTopologyElement()->getId()) +
                        ", but received " + std::to_string(sub_machine_id) +
                        " in the file " + path);
                }
                else {
                    job_sub_path_nodes.push_back(parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, serial_group_children_path_nodes[serial_group_children_index]}}));
                    serial_group_children_index++;
                }
            }

            for (int i = 0; i < job_sub_path_nodes.size() - 1; i++) {
                connectGraphsOfJobPathNodes(job_sub_path_nodes[i], job_sub_path_nodes[i + 1]);
            }
            serial_group_job_path_node->setNext(job_sub_path_nodes[0]);
        }

        else {
            auto child_path_node = ((SerialGroupPathNode*)path_node)->getNext();
            if (child_path_node) {
                serial_group_job_path_node->setNext(parsePathNodeWithoutYAMLNode(path, child_path_node));
            }
        }
    }

    else if (path_node_topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_job_path_node = new ParallelGroupJobPathNode(path_node);
        job_path_node = parallel_group_job_path_node;

        const YAML::Node& sub_machines_node = node["sub_machines"];

        if (sub_machines_node) {
            for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                long sub_machine_id = (*sub_machine_it)["machine_id"].as<long>();
                auto sub_machine_path_nodes = ((ParallelGroupPathNode*)path_node)->getNext();
                auto child_path_node = sub_machine_path_nodes.find(sub_machine_id)->second;
                if (!child_path_node) {
                    std::string legal_child_ids = "[";
                    for (auto & sub_machine_path_node : sub_machine_path_nodes) {
                        legal_child_ids += std::to_string(sub_machine_path_node.first) + ", ";
                    }
                    legal_child_ids += "]";
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                        ", expected 'machine_id' to be in " + legal_child_ids +
                        ", but received " + std::to_string(sub_machine_id) +
                        " in the file " + path);
                }
                parallel_group_job_path_node->setNext(sub_machine_id, parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_path_node}}));
            }
        }

        else {
            auto child_path_nodes = ((ParallelGroupPathNode*)path_node)->getNext();
            for (auto & child_path_node : child_path_nodes) {
                parallel_group_job_path_node->setNext(child_path_node.first, parsePathNodeWithoutYAMLNode(path, child_path_node.second));
            }
        }
    }

    else if (path_node_topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto route_group_job_path_node = new RouteGroupJobPathNode(path_node);
        job_path_node = route_group_job_path_node;

        const YAML::Node& sub_machines_node = node["sub_machines"];

        if (sub_machines_node) {
            std::vector<JobPathNode*> job_sub_path_nodes;
            for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                long sub_machine_id = (*sub_machine_it)["machine_id"].as<long>();
                auto sub_machine_path_nodes = ((RouteGroupPathNode*)path_node)->getSubPathNodes();
                PathNode* child_path_node = nullptr;
                for (auto sub_machine_path_node : sub_machine_path_nodes) {
                    if (sub_machine_id == sub_machine_path_node->getTopologyElement()->getId()) {
                        child_path_node = sub_machine_path_node;
                        break;
                    }
                }
                if (!child_path_node) {
                    std::string legal_child_ids = "[";
                    for (auto & sub_machine_path_node : sub_machine_path_nodes) {
                        legal_child_ids += std::to_string(sub_machine_path_node->getTopologyElement()->getId()) + ", ";
                    }
                    legal_child_ids += "]";
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          ", expected 'machine_id' to be in " + legal_child_ids +
                                          ", but received " + std::to_string(sub_machine_id) +
                                          " in the file " + path);
                }
                else {
                    job_sub_path_nodes.push_back(parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_path_node}}));
                }
            }

            for (int i = 0; i < job_sub_path_nodes.size() - 1; i++) {
                connectGraphsOfJobPathNodes(job_sub_path_nodes[i], job_sub_path_nodes[i + 1]);
            }
            auto child_path_node = ((RouteGroupPathNode*)path_node)->getNext();
            if (child_path_node) {
                auto child_job_path_node = parsePathNodeWithoutYAMLNode(path, child_path_node);
                connectGraphsOfJobPathNodes(job_sub_path_nodes.back(), child_job_path_node);
            }

            route_group_job_path_node->setNext(job_sub_path_nodes[0]);
        }

        else {
            auto child_path_node = ((RouteGroupPathNode*)path_node)->getNext();
            if (child_path_node) {
                route_group_job_path_node->setNext(parsePathNodeWithoutYAMLNode(path, child_path_node));
            }
        }
    }

    else if (path_node_topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto open_group_job_path_node = new OpenGroupJobPathNode(path_node);
        job_path_node = open_group_job_path_node;

        const YAML::Node& sub_machines_node = node["sub_machines"];

        if (sub_machines_node) {
            std::vector<JobPathNode*> job_sub_path_nodes;
            for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                long sub_machine_id = (*sub_machine_it)["machine_id"].as<long>();
                auto sub_machine_path_nodes = ((OpenGroupPathNode*)path_node)->getSubPathNodes();
                PathNode* child_path_node = nullptr;
                for (auto sub_machine_path_node : sub_machine_path_nodes) {
                    if (sub_machine_id == sub_machine_path_node->getTopologyElement()->getId()) {
                        child_path_node = sub_machine_path_node;
                        break;
                    }
                }
                if (!child_path_node) {
                    std::string legal_child_ids = "[";
                    for (auto & sub_machine_path_node : sub_machine_path_nodes) {
                        legal_child_ids += std::to_string(sub_machine_path_node->getTopologyElement()->getId()) + ", ";
                    }
                    legal_child_ids += "]";
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          ", expected 'machine_id' to be in " + legal_child_ids +
                                          ", but received " + std::to_string(sub_machine_id) +
                                          " in the file " + path);
                }
                else {
                    job_sub_path_nodes.push_back(parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_path_node}}));
                }
            }

            for (int i = 0; i < job_sub_path_nodes.size() - 1; i++) {
                connectGraphsOfJobPathNodes(job_sub_path_nodes[i], job_sub_path_nodes[i + 1]);
            }
            auto child_path_node = ((RouteGroupPathNode*)path_node)->getNext();
            if (child_path_node) {
                auto child_job_path_node = parsePathNodeWithoutYAMLNode(path, child_path_node);
                connectGraphsOfJobPathNodes(job_sub_path_nodes.back(), child_job_path_node);
            }

            open_group_job_path_node->setNext(job_sub_path_nodes[0]);
        }

        else {
            auto child_path_node = ((OpenGroupPathNode*)path_node)->getNext();
            if (child_path_node) {
                open_group_job_path_node->setNext(parsePathNodeWithoutYAMLNode(path, child_path_node));
            }
        }
    }

    const YAML::Node& prerequisites_node = node["prerequisites"];
    if (prerequisites_node) {
        for (YAML::const_iterator prerequisite_it = prerequisites_node.begin(); prerequisite_it != prerequisites_node.end(); prerequisite_it++) {
            if (!(*prerequisite_it)["job_id"]) {
                throw SchedulingError("Entry in the 'prerequisites' array must contain 'job_id' field in the file " + path);
            }
            long job_id = (*prerequisite_it)["job_id"].as<long>();
            if (!(*prerequisite_it)["machine_id"]) {
                throw SchedulingError("Entry in the 'prerequisites' array must contain 'machine_id' field in the file " + path);
            }
            long machine_id = (*prerequisite_it)["machine_id"].as<long>();
            long repetitions = (*prerequisite_it)["repetitions"] ? (*prerequisite_it)["repetitions"].as<long>() : 1;
            job_path_node->addPrerequisite(new Prerequisite(job_id, machine_id, repetitions));
        }
    }

    return job_path_node;
}

JobPathNode *JobSequenceParser::parsePathNodeWithoutYAMLNode(const std::string &path, PathNode* path_node) {

    auto path_node_topology_element_type = path_node->getTopologyElement()->getTopologyElementType();
    long machine_id = path_node->getTopologyElement()->getId();

    if (path_node_topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in the file " + path);
    }

    else if (path_node_topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_path_node = (MachinePathNode*) path_node;
        auto machine_job_path_node = new MachineJobPathNode(path_node);
        auto child_path_node = machine_path_node->getNext();
        if (child_path_node) {
            machine_job_path_node->setNext(parsePathNodeWithoutYAMLNode(path, child_path_node));
        }
        return machine_job_path_node;
    }

    else if (path_node_topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto serial_group_path_node = (SerialGroupPathNode*) path_node;
        auto serial_group_job_path_node = new SerialGroupJobPathNode(path_node);
        auto child_path_node = serial_group_path_node->getNext();
        if (child_path_node) {
            serial_group_job_path_node->setNext(parsePathNodeWithoutYAMLNode(path, child_path_node));
        }
        return serial_group_job_path_node;
    }

    else if (path_node_topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_path_node = (ParallelGroupPathNode*) path_node;
        auto parallel_group_job_path_node = new ParallelGroupJobPathNode(path_node);
        auto child_path_nodes = parallel_group_path_node->getNext();
        for (auto & child_path_node : child_path_nodes) {
            parallel_group_job_path_node->setNext(child_path_node.first, parsePathNodeWithoutYAMLNode(path, child_path_node.second));
        }
        return parallel_group_job_path_node;
    }

    else if (path_node_topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto route_group_path_node = (RouteGroupPathNode*) path_node;
        auto route_group_job_path_node = new RouteGroupJobPathNode(path_node);
        auto child_path_node = route_group_path_node->getNext();
        if (child_path_node) {
            route_group_job_path_node->setNext(parsePathNodeWithoutYAMLNode(path, child_path_node));
        }
        return route_group_job_path_node;
    }

    else if (path_node_topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto open_group_path_node = (OpenGroupPathNode*) path_node;
        auto open_group_job_path_node = new OpenGroupJobPathNode(path_node);
        auto child_path_node = open_group_path_node->getNext();
        if (child_path_node) {
            open_group_job_path_node->setNext(parsePathNodeWithoutYAMLNode(path, child_path_node));
        }
        return open_group_job_path_node;
    }
}

void JobSequenceParser::connectGraphsOfJobPathNodes(JobPathNode *job_path_node, JobPathNode *next_job_path_node) {

    switch (job_path_node->getPathNode()->getTopologyElement()->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in JobSequenceParser::connectGraphsOfJobPathNodes function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            if (((MachineJobPathNode*)job_path_node)->getNext()) {
                connectGraphsOfJobPathNodes(((MachineJobPathNode *) job_path_node)->getNext(), next_job_path_node);
            }
            else {
                ((MachineJobPathNode*)job_path_node)->setNext(next_job_path_node);
            }
            break;

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            if (((SerialGroupJobPathNode*)job_path_node)->getNext()) {
                connectGraphsOfJobPathNodes(((SerialGroupJobPathNode *) job_path_node)->getNext(), next_job_path_node);
            }
            else {
                ((SerialGroupJobPathNode*)job_path_node)->setNext(next_job_path_node);
            }
            break;

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            if (!((ParallelGroupJobPathNode*)job_path_node)->getNext().empty()) {
                for (auto & child : ((ParallelGroupJobPathNode*)job_path_node)->getNext()) {
                    connectGraphsOfJobPathNodes(child.second, next_job_path_node);
                }
            }
            else {
                ((ParallelGroupJobPathNode*)job_path_node)->setNext(next_job_path_node->getPathNode()->getTopologyElement()->getId(), next_job_path_node);
            }
            break;

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            if (((RouteGroupJobPathNode*)job_path_node)->getNext()) {
                connectGraphsOfJobPathNodes(((RouteGroupJobPathNode *) job_path_node)->getNext(), next_job_path_node);
            }
            else {
                ((RouteGroupJobPathNode*)job_path_node)->setNext(next_job_path_node);
            }
            break;

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            if (((OpenGroupJobPathNode*)job_path_node)->getNext()) {
                connectGraphsOfJobPathNodes(((OpenGroupJobPathNode *) job_path_node)->getNext(), next_job_path_node);
            }
            else {
                ((OpenGroupJobPathNode*)job_path_node)->setNext(next_job_path_node);
            }
            break;
    }
}