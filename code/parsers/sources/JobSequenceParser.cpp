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
#include "Machine.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "OpenGroup.h"
#include "yaml-cpp/yaml.h"

std::map<long, Job *> JobSequenceParser::parse(const std::string &path, MachineTypeMap *machine_type_map, JobTypeMap *job_type_map, Topology *topology) {

    std::map<long, Job*> jobs;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node job_sequence_node = doc["job_sequence"];

    if (job_sequence_node) {
        for (YAML::const_iterator it = job_sequence_node.begin(); it != job_sequence_node.end(); it++) {
            if (!(*it)["job_id"]) {
                throw SchedulingError("Entry in the 'job_sequence' array must contain 'job_id' field in the file " + path);
            }
            long job_id = (*it)["job_id"].as<long>();
            if (!(*it)["job_type_id"]) {
                throw SchedulingError("Entry in the 'job_sequence' array must contain 'job_type_id' field in the file " + path);
            }
            long job_type_id = (*it)["job_type_id"].as<long>();
            JobType* job_type = job_type_map->getJobType(job_type_id);
            long release_time = ((*it)["release_time"]) ? (*it)["release_time"].as<long>() : 0;
            long due_time = ((*it)["due_time"]) ? (*it)["due_time"].as<long>() : release_time;
            long weight = ((*it)["weight"]) ? (*it)["weight"].as<long>() : 1;

            PathNode* paths_root_node = nullptr;
            const YAML::Node& processing_route_node = (*it)["processing_route"];
            if (processing_route_node) {
                if (processing_route_node.size() != 1) {
                    throw SchedulingError("'processing_route' node for job with id " + std::to_string(job_id) + " can have only one child in " + path + " file.");
                }
                auto forbidden_machine_types = job_type_map->getJobType(job_type_id)->getForbiddenMachineTypes();
                // todo
                paths_root_node = parsePathNodeWithYAMLNode(*processing_route_node.begin(), path,
                    {{topology->getRootElement()->getId(), topology->getRootElement()}}, machine_type_map, forbidden_machine_types);
                if (!paths_root_node) {
                    throw SchedulingError("Cannot construct any job paths for job of id " + std::to_string(job_id) + " in function JobSequenceParser::parse.");
                }
            }
            else {
                throw SchedulingError("'processing_route' node for job with id " + std::to_string(job_id) + " not found in " + path + " file.");
            }

            Job* job = new Job(job_id, job_type, paths_root_node, release_time, due_time, weight);
            jobs[job_id] = job;
        }
    }

    else {
        throw SchedulingError("'job_sequence' node not found in " + path + " file.");
    }

    for (auto & job_pair : jobs) {
        calculateJobProcessingTimes(job_pair.second, topology);
    }

    return jobs;
}

PathNode *JobSequenceParser::parsePathNodeWithYAMLNode(const YAML::Node &node, const std::string &path, std::map<long, TopologyElement *> legal_topology_elements, MachineTypeMap *machine_type_map, const std::set<long> &forbidden_machine_types) {
    if (!node["machine_id"]) {
        throw SchedulingError("Entry in the 'topology' or 'sub_machines' arrays must contain 'machine_id' field in the file " + path);
    }
    long machine_id = node["machine_id"].as<long>();

    auto topology_element = legal_topology_elements.find(machine_id)->second;
    if (topology_element == nullptr) {
        throw SchedulingError("Entry in the 'sub_machines' array contains invalid 'machine_id' value of " + std::to_string(machine_id)  + " in the file " + path);
    }

    auto path_node_topology_element_type = topology_element->getTopologyElementType();

    if (path_node_topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_type_id = ((Machine*) topology_element)->getMachineType()->getId();
        auto machine_type = machine_type_map->getMachineType(machine_type_id);
        if (!machine_type) {
            throw SchedulingError("Machine of id " + std::to_string(machine_id) + " has no machine_type in JobSequenceParser::parsePathNodeWithoutYAMLNode function.");
        }
        if (forbidden_machine_types.find(machine_type_id) != forbidden_machine_types.end()) {
            return nullptr;
        }
    }

    PathNode* path_node = nullptr;

    if (path_node_topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in the file " + path);
    }

    else if (path_node_topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_element = (Machine*) topology_element;
        auto machine_path_node = new MachinePathNode(machine_element);
        path_node = machine_path_node;
        const YAML::Node& sub_machines_node = node["sub_machines"];
        if (sub_machines_node) {
            throw SchedulingError("Machine topology element of id " + std::to_string(machine_id) +  " cannot have sub_machines in the file " + path);
        }
    }

    else if (path_node_topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto serial_group_element = (SerialGroup*) topology_element;
        auto serial_group_path_node = new SerialGroupPathNode(serial_group_element);
        path_node = serial_group_path_node;
        auto serial_group_children = serial_group_element->getChildren();
        std::vector<PathNode*> child_path_nodes;

        const YAML::Node& sub_machines_node = node["sub_machines"];

        if (sub_machines_node) {
            long serial_group_children_index = 0;
            for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                long sub_machine_id = (*sub_machine_it)["machine_id"].as<long>();
                if (sub_machine_id != serial_group_children[serial_group_children_index]->getId()) {
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                        ", expected 'machine_id' to be equal to " + std::to_string(serial_group_children[serial_group_children_index]->getId()) +
                        ", but received " + std::to_string(sub_machine_id) +
                        " in the file " + path);
                }
                else {
                    auto serial_group_child_path_node = parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, serial_group_children[serial_group_children_index]}}, machine_type_map, forbidden_machine_types);
                    if (!serial_group_child_path_node) {
                        for (auto & child_path_node : child_path_nodes) {
                            child_path_node->deletePathNode();
                        }
                        serial_group_path_node->deletePathNode();
                        return nullptr;
                    }
                    child_path_nodes.push_back(serial_group_child_path_node);
                    serial_group_children_index++;
                }
            }

            if (serial_group_children_index != serial_group_children.size()) {
                throw SchedulingError("Not enough entries in the 'sub_machines' array for machine of id " + std::to_string(machine_id) + " in the file " + path);
            }

            for (int i = 0; i < child_path_nodes.size() - 1; i++) {
                connectGraphsOfPathNodes(child_path_nodes[i], child_path_nodes[i + 1]);
            }
            serial_group_path_node->setNext(child_path_nodes[0]);
        }

        else {
            for (auto child_element : serial_group_children) {
                auto child_path_node = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types);
                if (!child_path_node) {
                    for (auto child : child_path_nodes) {
                        child->deletePathNode();
                    }
                    serial_group_path_node->deletePathNode();
                    return nullptr;
                }
                child_path_nodes.push_back(child_path_node);
            }
            if (child_path_nodes.empty()) {
                serial_group_path_node->deletePathNode();
                return nullptr;
            }
            for (int i = 0; i < child_path_nodes.size() - 1; i++) {
                connectGraphsOfPathNodes(child_path_nodes[i], child_path_nodes[i + 1]);
            }
            connectGraphsOfPathNodes(serial_group_path_node, child_path_nodes[0]);
            return serial_group_path_node;
        }
    }

    else if (path_node_topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_element = (ParallelGroup*) topology_element;
        auto parallel_group_path_node = new ParallelGroupPathNode(parallel_group_element);
        path_node = parallel_group_path_node;
        auto parallel_group_children = parallel_group_element->getChildren();

        const YAML::Node& sub_machines_node = node["sub_machines"];

        if (sub_machines_node) {
            for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                long sub_machine_id = (*sub_machine_it)["machine_id"].as<long>();
                TopologyElement* child_element = nullptr;
                for (auto child : parallel_group_children) {
                    if (child->getId() == sub_machine_id) {
                        child_element = child;
                        break;
                    }
                }
                if (!child_element) {
                    std::string legal_child_ids = "[";
                    for (auto & child : parallel_group_children) {
                        legal_child_ids += std::to_string(child->getId()) + ", ";
                    }
                    legal_child_ids += "]";
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                        ", expected 'machine_id' to be in " + legal_child_ids +
                        ", but received " + std::to_string(sub_machine_id) +
                        " in the file " + path);
                }
                auto parallel_group_job_path_node_child = parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_element}}, machine_type_map, forbidden_machine_types);
                if (parallel_group_job_path_node_child) {
                    parallel_group_path_node->setNext(sub_machine_id, parallel_group_job_path_node_child);
                }
            }

            for (auto child_element : parallel_group_children) {
                if (parallel_group_path_node->getNext().find(child_element->getId()) == parallel_group_path_node->getNext().end()) {
                    auto child_path_node = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types);
                    if (child_path_node) {
                        parallel_group_path_node->setNext(child_element->getId(), child_path_node);
                    }
                }
            }

            if (parallel_group_path_node->getNext().empty()) {
                parallel_group_path_node->deletePathNode();
                return nullptr;
            }
        }

        else {
            for (auto child_element : parallel_group_children) {
                auto child_path_node = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types);
                if (child_path_node) {
                    parallel_group_path_node->setNext(child_element->getId(), child_path_node);
                }
            }
            if (parallel_group_path_node->getNext().empty()) {
                parallel_group_path_node->deletePathNode();
                return nullptr;
            }
        }
    }

    else if (path_node_topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto route_group_element = (RouteGroup*) topology_element;
        auto route_group_path_node = new RouteGroupPathNode(route_group_element);
        path_node = route_group_path_node;
        auto route_group_children = route_group_element->getChildren();

        const YAML::Node& sub_machines_node = node["sub_machines"];

        if (sub_machines_node) {
            std::vector<PathNode*> route_group_child_path_nodes;
            for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                long sub_machine_id = (*sub_machine_it)["machine_id"].as<long>();
                TopologyElement* child_element = nullptr;
                for (auto child : route_group_children) {
                    if (child->getId() == sub_machine_id) {
                        child_element = child;
                        break;
                    }
                }

                if (!child_element) {
                    std::string legal_child_ids = "[";
                    for (auto & child : route_group_children) {
                        legal_child_ids += std::to_string(child->getId()) + ", ";
                    }
                    legal_child_ids += "]";
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          ", expected 'machine_id' to be in " + legal_child_ids +
                                          ", but received " + std::to_string(sub_machine_id) +
                                          " in the file " + path);
                }
                else {
                    auto route_group_child_path_node = parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_element}}, machine_type_map, forbidden_machine_types);
                    if (!route_group_child_path_node) {
                        for (auto & child_path_node : route_group_child_path_nodes) {
                            child_path_node->deletePathNode();
                        }
                        route_group_path_node->deletePathNode();
                        return nullptr;
                    }
                    route_group_child_path_nodes.push_back(route_group_child_path_node);
                }
            }

            for (int i = 0; i < route_group_child_path_nodes.size() - 1; i++) {
                connectGraphsOfPathNodes(route_group_child_path_nodes[i], route_group_child_path_nodes[i + 1]);
            }
            route_group_path_node->setNext(route_group_child_path_nodes[0]);
        }
    }

    else if (path_node_topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto open_group_element = (OpenGroup*) topology_element;
        auto open_group_path_node = new OpenGroupPathNode(open_group_element);
        path_node = open_group_path_node;
        auto open_group_children = open_group_element->getChildren();

        const YAML::Node& sub_machines_node = node["sub_machines"];

        if (sub_machines_node) {
            for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                long sub_machine_id = (*sub_machine_it)["machine_id"].as<long>();
                TopologyElement* child_element = nullptr;
                for (auto child : open_group_children) {
                    if (child->getId() == sub_machine_id) {
                        child_element = child;
                        break;
                    }
                }


                if (!child_element) {
                    std::string legal_child_ids = "[";
                    for (auto & child : open_group_children) {
                        legal_child_ids += std::to_string(child->getId()) + ", ";
                    }
                    legal_child_ids += "]";
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          ", expected 'machine_id' to be in " + legal_child_ids +
                                          ", but received " + std::to_string(sub_machine_id) +
                                          " in the file " + path);
                }
                else {
                    auto open_group_child_path_node = parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_element}}, machine_type_map, forbidden_machine_types);
                    if (!open_group_child_path_node) {
                        open_group_path_node->deletePathNode();
                        return nullptr;
                    }
                    open_group_path_node->addSubPathNode(sub_machine_id, open_group_child_path_node);
                }
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
            path_node->addPrerequisite(new Prerequisite(job_id, machine_id, repetitions));
        }
    }

    return path_node;
}

PathNode *JobSequenceParser::parsePathNodeWithoutYAMLNode(const std::string &path, TopologyElement *topology_element, MachineTypeMap *machine_type_map, const std::set<long> &forbidden_machine_types) {
    auto topology_element_type = topology_element->getTopologyElementType();
    auto machine_id = topology_element->getId();

    if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_type_id = ((Machine*) topology_element)->getMachineType()->getId();
        auto machine_type = machine_type_map->getMachineType(machine_type_id);
        if (!machine_type) {
            throw SchedulingError("Machine of id " + std::to_string(machine_id) + " has no machine_type in JobSequenceParser::parsePathNodeWithoutYAMLNode function.");
        }
        if (forbidden_machine_types.find(machine_type_id) != forbidden_machine_types.end()) {
            return nullptr;
        }
    }

    if (topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in the file " + path);
    }

    else if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_element = (Machine*) topology_element;
        auto machine_path_node = new MachinePathNode(machine_element);
        return machine_path_node;
    }

    else if (topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto serial_group_element = (SerialGroup*) topology_element;
        auto serial_group_path_node = new SerialGroupPathNode(serial_group_element);
        std::vector<PathNode*> child_path_nodes;
        for (auto child_element : serial_group_element->getChildren()) {
            auto child_path_node = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types);
            if (!child_path_node) {
                for (auto child : child_path_nodes) {
                    child->deletePathNode();
                }
                serial_group_path_node->deletePathNode();
                return nullptr;
            }
            child_path_nodes.push_back(child_path_node);
        }
        if (child_path_nodes.empty()) {
            serial_group_path_node->deletePathNode();
            return nullptr;
        }
        for (int i = 0; i < child_path_nodes.size() - 1; i++) {
            connectGraphsOfPathNodes(child_path_nodes[i], child_path_nodes[i + 1]);
        }
        connectGraphsOfPathNodes(serial_group_path_node, child_path_nodes[0]);
        return serial_group_path_node;
    }

    else if (topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_element = (ParallelGroup*) topology_element;
        auto parallel_group_path_node = new ParallelGroupPathNode(parallel_group_element);
        for (auto child_element : parallel_group_element->getChildren()) {
            auto child_path_node = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types);
            if (child_path_node) {
                parallel_group_path_node->setNext(child_element->getId(), child_path_node);
            }
        }
        if (parallel_group_path_node->getNext().empty()) {
            parallel_group_path_node->deletePathNode();
            return nullptr;
        }
        return parallel_group_path_node;
    }

    else if (topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto route_group_element = (RouteGroup*) topology_element;
        auto route_group_path_node = new RouteGroupPathNode(route_group_element);
        return route_group_path_node;
    }

    else if (topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto open_group_element = (OpenGroup*) topology_element;
        auto open_group_path_node = new OpenGroupPathNode(open_group_element);
        return open_group_path_node;
    }
}

void JobSequenceParser::connectGraphsOfPathNodes(PathNode *path_node, PathNode *next_path_node) {

    switch (path_node->getTopologyElement()->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in JobSequenceParser::connectGraphsOfJobPathNodes function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            if (((MachinePathNode*)path_node)->getNext()) {
                connectGraphsOfPathNodes(((MachinePathNode *) path_node)->getNext(), next_path_node);
            }
            else {
                ((MachinePathNode*)path_node)->setNext(next_path_node);
            }
            break;

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            if (((SerialGroupPathNode*)path_node)->getNext()) {
                connectGraphsOfPathNodes(((SerialGroupPathNode *) path_node)->getNext(), next_path_node);
            }
            else {
                ((SerialGroupPathNode*)path_node)->setNext(next_path_node);
            }
            break;

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            if (!((ParallelGroupPathNode*)path_node)->getNext().empty()) {
                for (auto & child : ((ParallelGroupPathNode*)path_node)->getNext()) {
                    connectGraphsOfPathNodes(child.second, next_path_node);
                }
            }
            else {
                ((ParallelGroupPathNode*)path_node)->setNext(next_path_node->getTopologyElement()->getId(), next_path_node);
            }
            break;

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            if (((RouteGroupPathNode*)path_node)->getNext()) {
                connectGraphsOfPathNodes(((RouteGroupPathNode *) path_node)->getNext(), next_path_node);
            }
            else {
                ((RouteGroupPathNode*)path_node)->setNext(next_path_node);
            }
            break;

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            if (((OpenGroupPathNode*)path_node)->getNext()) {
                connectGraphsOfPathNodes(((OpenGroupPathNode *) path_node)->getNext(), next_path_node);
            }
            else {
                ((OpenGroupPathNode*)path_node)->setNext(next_path_node);
            }
            break;
    }
}

void JobSequenceParser::calculateJobProcessingTimes(Job *job, Topology *topology) {

    for (auto topology_element_pair : topology->getTopologyElementsMap()) {
        auto topology_element = topology_element_pair.second;

        switch (topology_element->getGeneralTopologyElementType()) {

            case ABSTRACT_GENERAL_TOPOLOGY_ELEMENT:
                throw SchedulingError("Abstract topology element encountered in function JobSequenceParser::calculateJobProcessingTimes.");

            case MACHINE_GENERAL_TOPOLOGY_ELEMENT:
                job->addProcessingTime(topology_element->getId(), job->getJobType()->getProcessingTime(((Machine*)topology_element)->getMachineType()->getId()));
                break;

            case GROUP_GENERAL_TOPOLOGY_ELEMENT:
                job->addProcessingTime(topology_element->getId(), 0);
                break;
        }
    }
}