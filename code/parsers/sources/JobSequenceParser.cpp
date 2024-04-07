//
// Created by mihael on 29/04/23.
//

#include "JobSequenceParser.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "OpenGroupPathNode.h"
#include "MachinePathTreeNode.h"
#include "SerialGroupPathTreeNode.h"
#include "ParallelGroupPathTreeNode.h"
#include "RouteGroupPathTreeNode.h"
#include "OpenGroupPathTreeNode.h"
#include "Machine.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "OpenGroup.h"
#include "yaml-cpp/yaml.h"
#include "ranges"

std::map<long, Job *> JobSequenceParser::parse(const std::string &path, MachineTypeMap *machine_type_map, JobTypeMap *job_type_map, Topology *topology) {

    std::map<long, Job*> jobs;

    YAML::Node doc = YAML::LoadFile(path);

    if (YAML::Node job_sequence_node = doc["job_sequence"]; job_sequence_node) {
        for (YAML::const_iterator it = job_sequence_node.begin(); it != job_sequence_node.end(); ++it) {
            if (!(*it)["job_id"]) {
                throw SchedulingError("Entry in the 'job_sequence' array must contain 'job_id' field in the file " + path);
            }
            long job_id = (*it)["job_id"].as<long>();
            if (!(*it)["job_type_id"]) {
                throw SchedulingError("Entry in the 'job_sequence' array must contain 'job_type_id' field in the file " + path);
            }
            long const job_type_id = (*it)["job_type_id"].as<long>();
            JobType* job_type = job_type_map->getJobType(job_type_id);
            double const release_time = (*it)["release_time"] ? (*it)["release_time"].as<double>() : 0;
            double const due_time = (*it)["due_time"] ? (*it)["due_time"].as<double>() : release_time;
            double const weight = (*it)["weight"] ? (*it)["weight"].as<double>() : 1;

            PathNode* paths_root_node = nullptr;
            PathTreeNode* paths_root_tree_node = nullptr;
            if (const YAML::Node& processing_route_node = (*it)["processing_route"]; processing_route_node) {
                if (processing_route_node.size() != 1) {
                    throw SchedulingError("'processing_route' node for job with id " + std::to_string(job_id) + " can have only one child in " + path + " file.");
                }
                auto forbidden_machine_types = job_type_map->getJobType(job_type_id)->getForbiddenMachineTypes();
                std::tie(paths_root_node, paths_root_tree_node, std::ignore) = parsePathNodeWithYAMLNode(*processing_route_node.begin(), path,
                    {{topology->getRootElement()->getId(), topology->getRootElement()}}, machine_type_map, forbidden_machine_types, 1);
                if (!paths_root_node) {
                    throw SchedulingError("Cannot construct any job paths for job of id " + std::to_string(job_id) + " in function JobSequenceParser::parse.");
                }
            }
            else {
                throw SchedulingError("'processing_route' node for job with id " + std::to_string(job_id) + " not found in " + path + " file.");
            }

            auto const job = new Job(job_id, job_type, paths_root_node, paths_root_tree_node, release_time, due_time, weight);
            jobs[job_id] = job;
        }
    }

    else {
        throw SchedulingError("'job_sequence' node not found in " + path + " file.");
    }

    for (auto const & job : jobs | std::views::values) {
        calculateJobProcessingTimes(job, topology);
    }

    return jobs;
}

std::tuple<PathNode*, PathTreeNode*, long> JobSequenceParser::parsePathNodeWithYAMLNode(const YAML::Node &node, const std::string &path, std::map<long, TopologyElement *> legal_topology_elements, MachineTypeMap *machine_type_map, const std::set<long> &forbidden_machine_types, long path_tree_node_id) {
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
        auto const machine_type_id = dynamic_cast<Machine*>(topology_element)->getMachineType()->getId();
        if (auto const machine_type = machine_type_map->getMachineType(machine_type_id); !machine_type) {
            throw SchedulingError("Machine of id " + std::to_string(machine_id) + " has no machine_type in JobSequenceParser::parsePathNodeWithoutYAMLNode function.");
        }
        if (forbidden_machine_types.contains(machine_type_id)) {
            return {nullptr, nullptr, -1};
        }
    }

    PathNode* path_node = nullptr;
    PathTreeNode* path_tree_node = nullptr;

    if (path_node_topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in the file " + path);
    }

    if (path_node_topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_element = dynamic_cast<Machine*>(topology_element);
        auto machine_path_node = new MachinePathNode(path_tree_node_id, machine_element);
        auto machine_path_tree_node = new MachinePathTreeNode(machine_path_node);
        path_tree_node_id++;
        path_node = machine_path_node;
        path_tree_node = machine_path_tree_node;
        if (const YAML::Node& sub_machines_node = node["sub_machines"]; sub_machines_node) {
            throw SchedulingError("Machine topology element of id " + std::to_string(machine_id) +  " cannot have sub_machines in the file " + path);
        }
    }

    else if (path_node_topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto serial_group_element = dynamic_cast<SerialGroup*>(topology_element);
        auto serial_group_path_node = new SerialGroupPathNode(path_tree_node_id, serial_group_element);
        auto serial_group_path_tree_node = new SerialGroupPathTreeNode(serial_group_path_node);
        path_tree_node_id++;
        path_node = serial_group_path_node;
        path_tree_node = serial_group_path_tree_node;
        auto serial_group_children = serial_group_element->getChildren();
        std::vector<PathNode*> child_path_nodes;
        std::vector<PathTreeNode*> child_path_tree_nodes;

        if (const YAML::Node& sub_machines_node = node["sub_machines"]; sub_machines_node) {
            long serial_group_children_index = 0;
            for (auto sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); ++sub_machine_it) {
                if (!(*sub_machine_it)["machine_id"]) {
                    throw SchedulingError("Entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                                          " does not contain a 'machine_id' field in the file " + path);
                }
                if (long const sub_machine_id = (*sub_machine_it)["machine_id"].as<long>(); sub_machine_id != serial_group_children[serial_group_children_index]->getId()) {
                    throw SchedulingError("Invalid entry in the 'sub_machines' array for machine of id " + std::to_string(machine_id) +
                        ", expected 'machine_id' to be equal to " + std::to_string(serial_group_children[serial_group_children_index]->getId()) +
                        ", but received " + std::to_string(sub_machine_id) +
                        " in the file " + path);
                }
                else {
                    auto [serial_group_child_path_node, serial_group_child_path_tree_node, child_path_tree_node_id] = parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, serial_group_children[serial_group_children_index]}}, machine_type_map, forbidden_machine_types, path_tree_node_id);
                    if (!serial_group_child_path_node) {
                        for (auto & child_path_tree_node : child_path_tree_nodes) {
                            child_path_tree_node->deletePathTreeNode();
                        }
                        for (auto & child_path_node : child_path_nodes) {
                            child_path_node->deletePathNode();
                        }
                        serial_group_path_tree_node->deletePathTreeNode();
                        serial_group_path_node->deletePathNode();
                        return {nullptr, nullptr, -1};
                    }
                    child_path_nodes.push_back(serial_group_child_path_node);
                    child_path_tree_nodes.push_back(serial_group_child_path_tree_node);
                    path_tree_node_id = child_path_tree_node_id;
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
            for (auto child : child_path_tree_nodes) {
                serial_group_path_tree_node->addChild(child);
            }
        }

        else {
            for (auto child_element : serial_group_children) {
                auto [child_path_node, child_path_tree_node, child_path_tree_node_id] = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types, path_tree_node_id);
                if (!child_path_node) {
                    for (auto child : child_path_tree_nodes) {
                        child->deletePathTreeNode();
                    }
                    for (auto child : child_path_nodes) {
                        child->deletePathNode();
                    }
                    serial_group_path_tree_node->deletePathTreeNode();
                    serial_group_path_node->deletePathNode();
                    return {nullptr, nullptr, -1};
                }
                child_path_nodes.push_back(child_path_node);
                child_path_tree_nodes.push_back(child_path_tree_node);
                path_tree_node_id = child_path_tree_node_id;
            }
            if (child_path_nodes.empty()) {
                serial_group_path_tree_node->deletePathTreeNode();
                serial_group_path_node->deletePathNode();
                return {nullptr, nullptr, -1};
            }
            for (int i = 0; i < child_path_nodes.size() - 1; i++) {
                connectGraphsOfPathNodes(child_path_nodes[i], child_path_nodes[i + 1]);
            }
            connectGraphsOfPathNodes(serial_group_path_node, child_path_nodes[0]);
            for (auto child : child_path_tree_nodes) {
                serial_group_path_tree_node->addChild(child);
            }
            return {serial_group_path_node, serial_group_path_tree_node, path_tree_node_id};
        }
    }

    else if (path_node_topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_element = dynamic_cast<ParallelGroup*>(topology_element);
        auto parallel_group_path_node = new ParallelGroupPathNode(path_tree_node_id, parallel_group_element);
        auto parallel_group_path_tree_node = new ParallelGroupPathTreeNode(parallel_group_path_node);
        path_tree_node_id++;
        path_node = parallel_group_path_node;
        path_tree_node = parallel_group_path_tree_node;
        auto parallel_group_children = parallel_group_element->getChildren();

        if (const YAML::Node& sub_machines_node = node["sub_machines"]; sub_machines_node) {
            std::set<long> failed_children_path_ids;
            for (auto sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); ++sub_machine_it) {
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
                if (auto [parallel_group_path_node_child, parallel_group_path_tree_node_child, child_path_tree_node_id] = parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_element}}, machine_type_map, forbidden_machine_types, path_tree_node_id); parallel_group_path_node_child) {
                    parallel_group_path_node->setNext(sub_machine_id, parallel_group_path_node_child);
                    parallel_group_path_tree_node->addChild(parallel_group_path_tree_node_child);
                    path_tree_node_id = child_path_tree_node_id;
                }
                else {
                    failed_children_path_ids.insert(child_element->getId());
                }
            }

            for (auto child_element : parallel_group_children) {
                if (!parallel_group_path_node->getNext().contains(child_element->getId()) && !failed_children_path_ids.contains(child_element->getId())) {
                    if (auto [child_path_node, child_path_tree_node, child_path_tree_node_id] = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types, path_tree_node_id); child_path_node) {
                        parallel_group_path_node->setNext(child_element->getId(), child_path_node);
                        parallel_group_path_tree_node->addChild(child_path_tree_node);
                        path_tree_node_id = child_path_tree_node_id;
                    }
                }
            }

            if (parallel_group_path_node->getNext().empty()) {
                parallel_group_path_tree_node->deletePathTreeNode();
                parallel_group_path_node->deletePathNode();
                return {nullptr, nullptr, -1};
            }
        }

        else {
            for (auto child_element : parallel_group_children) {
                if (auto [child_path_node, child_path_tree_node, child_path_tree_node_id] = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types, path_tree_node_id); child_path_node) {
                    parallel_group_path_node->setNext(child_element->getId(), child_path_node);
                    parallel_group_path_tree_node->addChild(child_path_tree_node);
                    path_tree_node_id = child_path_tree_node_id;
                }
            }
            if (parallel_group_path_node->getNext().empty()) {
                parallel_group_path_tree_node->deletePathTreeNode();
                parallel_group_path_node->deletePathNode();
                return {nullptr, nullptr, -1};
            }
        }
    }

    else if (path_node_topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto route_group_element = dynamic_cast<RouteGroup*>(topology_element);
        auto route_group_path_node = new RouteGroupPathNode(path_tree_node_id, route_group_element);
        auto route_group_path_tree_node = new RouteGroupPathTreeNode(route_group_path_node);
        path_tree_node_id++;
        path_node = route_group_path_node;
        path_tree_node = route_group_path_tree_node;
        auto route_group_children = route_group_element->getChildren();

        if (const YAML::Node& sub_machines_node = node["sub_machines"]; sub_machines_node) {
            std::vector<PathNode*> route_group_child_path_nodes;
            std::vector<PathTreeNode*> route_group_child_path_tree_nodes;
            for (auto sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); ++sub_machine_it) {
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
                auto [route_group_child_path_node, route_group_child_path_tree_node, child_path_tree_node_id] = parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_element}}, machine_type_map, forbidden_machine_types, path_tree_node_id);
                if (!route_group_child_path_node) {
                    for (auto & child_path_tree_node : route_group_child_path_tree_nodes) {
                        child_path_tree_node->deletePathTreeNode();
                    }
                    for (auto & child_path_node : route_group_child_path_nodes) {
                        child_path_node->deletePathNode();
                    }
                    route_group_path_tree_node->deletePathTreeNode();
                    route_group_path_node->deletePathNode();
                    return {nullptr, nullptr, -1};
                }
                route_group_child_path_nodes.push_back(route_group_child_path_node);
                route_group_child_path_tree_nodes.push_back(route_group_child_path_tree_node);
                path_tree_node_id = child_path_tree_node_id;
            }

            for (int i = 0; i < route_group_child_path_nodes.size() - 1; i++) {
                connectGraphsOfPathNodes(route_group_child_path_nodes[i], route_group_child_path_nodes[i + 1]);
            }
            for (auto child : route_group_child_path_tree_nodes) {
                route_group_path_tree_node->addChild(child);
            }
            route_group_path_node->setNext(route_group_child_path_nodes[0]);
        }
    }

    else if (path_node_topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto open_group_element = dynamic_cast<OpenGroup*>(topology_element);
        auto open_group_path_node = new OpenGroupPathNode(path_tree_node_id, open_group_element);
        auto open_group_path_tree_node = new OpenGroupPathTreeNode(open_group_path_node);
        path_tree_node_id++;
        path_node = open_group_path_node;
        path_tree_node = open_group_path_tree_node;
        auto open_group_children = open_group_element->getChildren();

        if (const YAML::Node& sub_machines_node = node["sub_machines"]; sub_machines_node) {
            for (auto sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); ++sub_machine_it) {
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
                auto [open_group_child_path_node, open_group_child_path_tree_node, child_path_tree_node_id] = parsePathNodeWithYAMLNode(*sub_machine_it, path, {{sub_machine_id, child_element}}, machine_type_map, forbidden_machine_types, path_tree_node_id);
                if (!open_group_child_path_node) {
                    open_group_path_tree_node->deletePathTreeNode();
                    open_group_path_node->deletePathNode();
                    return {nullptr, nullptr, -1};
                }
                open_group_path_node->addSubPathNode(sub_machine_id, open_group_child_path_node);
                open_group_path_tree_node->addChild(open_group_child_path_tree_node);
                path_tree_node_id = child_path_tree_node_id;
            }
        }
    }

    if (const YAML::Node& prerequisites_node = node["prerequisites"]; prerequisites_node) {
        for (auto prerequisite_it = prerequisites_node.begin(); prerequisite_it != prerequisites_node.end(); ++prerequisite_it) {
            if (!(*prerequisite_it)["job_id"]) {
                throw SchedulingError("Entry in the 'prerequisites' array must contain 'job_id' field in the file " + path);
            }
            long job_id = (*prerequisite_it)["job_id"].as<long>();
            if (!(*prerequisite_it)["machine_id"]) {
                throw SchedulingError("Entry in the 'prerequisites' array must contain 'machine_id' field in the file " + path);
            }
            long prerequisite_machine_id = (*prerequisite_it)["machine_id"].as<long>();
            long repetitions = (*prerequisite_it)["repetitions"] ? (*prerequisite_it)["repetitions"].as<long>() : 1;
            path_node->addPrerequisite(new Prerequisite(job_id, prerequisite_machine_id, repetitions));
        }
    }

    return {path_node, path_tree_node, path_tree_node_id};
}

std::tuple<PathNode*, PathTreeNode*, long> JobSequenceParser::parsePathNodeWithoutYAMLNode(const std::string &path, TopologyElement *topology_element, MachineTypeMap *machine_type_map, const std::set<long> &forbidden_machine_types, long path_tree_node_id) {
    auto const topology_element_type = topology_element->getTopologyElementType();
    auto const machine_id = topology_element->getId();

    if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto const machine_type_id = dynamic_cast<Machine*>(topology_element)->getMachineType()->getId();
        if (auto const machine_type = machine_type_map->getMachineType(machine_type_id); !machine_type) {
            throw SchedulingError("Machine of id " + std::to_string(machine_id) + " has no machine_type in JobSequenceParser::parsePathNodeWithoutYAMLNode function.");
        }
        if (forbidden_machine_types.contains(machine_type_id)) {
            return {nullptr, nullptr, -1};
        }
    }

    if (topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in the file " + path);
    }

    if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto const machine_element = dynamic_cast<Machine*>(topology_element);
        auto machine_path_node = new MachinePathNode(path_tree_node_id, machine_element);
        auto machine_path_tree_node = new MachinePathTreeNode(machine_path_node);
        path_tree_node_id++;
        return {machine_path_node, machine_path_tree_node, path_tree_node_id};
    }

    if (topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto const serial_group_element = dynamic_cast<SerialGroup*>(topology_element);
        auto serial_group_path_node = new SerialGroupPathNode(path_tree_node_id, serial_group_element);
        auto serial_group_path_tree_node = new SerialGroupPathTreeNode(serial_group_path_node);
        path_tree_node_id++;
        std::vector<PathNode*> child_path_nodes;
        std::vector<PathTreeNode*> child_path_tree_nodes;
        for (auto const child_element : serial_group_element->getChildren()) {
            auto [child_path_node, child_path_tree_node, child_path_tree_node_id] = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types, path_tree_node_id);
            if (!child_path_node) {
                for (auto const child : child_path_tree_nodes) {
                    child->deletePathTreeNode();
                }
                for (auto const child : child_path_nodes) {
                    child->deletePathNode();
                }
                serial_group_path_node->deletePathNode();
                serial_group_path_tree_node->deletePathTreeNode();
                return {nullptr, nullptr, -1};
            }
            child_path_nodes.push_back(child_path_node);
            child_path_tree_nodes.push_back(child_path_tree_node);
            path_tree_node_id = child_path_tree_node_id;
        }
        if (child_path_nodes.empty()) {
            serial_group_path_tree_node->deletePathTreeNode();
            serial_group_path_node->deletePathNode();
            return {nullptr, nullptr, -1};
        }
        for (int i = 0; i < child_path_nodes.size() - 1; i++) {
            connectGraphsOfPathNodes(child_path_nodes[i], child_path_nodes[i + 1]);
        }
        connectGraphsOfPathNodes(serial_group_path_node, child_path_nodes[0]);
        for (auto const child : child_path_tree_nodes) {
            serial_group_path_tree_node->addChild(child);
        }
        return {serial_group_path_node, serial_group_path_tree_node, path_tree_node_id};
    }

    if (topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto const parallel_group_element = dynamic_cast<ParallelGroup*>(topology_element);
        auto parallel_group_path_node = new ParallelGroupPathNode(path_tree_node_id, parallel_group_element);
        auto parallel_group_path_tree_node = new ParallelGroupPathTreeNode(parallel_group_path_node);
        path_tree_node_id++;
        for (auto const child_element : parallel_group_element->getChildren()) {
            if (auto [child_path_node, child_path_tree_node, child_path_tree_node_id] = parsePathNodeWithoutYAMLNode(path, child_element, machine_type_map, forbidden_machine_types, path_tree_node_id); child_path_node) {
                parallel_group_path_node->setNext(child_element->getId(), child_path_node);
                parallel_group_path_tree_node->addChild(child_path_tree_node);
                path_tree_node_id = child_path_tree_node_id;
            }
        }
        if (parallel_group_path_node->getNext().empty()) {
            parallel_group_path_tree_node->deletePathTreeNode();
            parallel_group_path_node->deletePathNode();
            return {nullptr, nullptr, -1};
        }
        return {parallel_group_path_node, parallel_group_path_tree_node, path_tree_node_id};
    }

    if (topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto const route_group_element = dynamic_cast<RouteGroup*>(topology_element);
        auto route_group_path_node = new RouteGroupPathNode(path_tree_node_id, route_group_element);
        auto route_group_path_tree_node = new RouteGroupPathTreeNode(route_group_path_node);
        path_tree_node_id++;
        return {route_group_path_node, route_group_path_tree_node, path_tree_node_id};
    }

    if (topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto const open_group_element = dynamic_cast<OpenGroup*>(topology_element);
        auto open_group_path_node = new OpenGroupPathNode(path_tree_node_id, open_group_element);
        auto open_group_path_tree_node = new OpenGroupPathTreeNode(open_group_path_node);
        path_tree_node_id++;
        return {open_group_path_node, open_group_path_tree_node, path_tree_node_id};
    }
}

void JobSequenceParser::connectGraphsOfPathNodes(PathNode *path_node, PathNode *next_path_node) {

    if (path_node == next_path_node) {
        return;
    }

    switch (path_node->getTopologyElement()->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in JobSequenceParser::connectGraphsOfJobPathNodes function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            {
                if (auto const machine_path_node = dynamic_cast<MachinePathNode*>(path_node); machine_path_node->getNext()) {
                    connectGraphsOfPathNodes(machine_path_node->getNext(), next_path_node);
                }
                else {
                    machine_path_node->setNext(next_path_node);
                }
                break;
            }

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const serial_group_path_node = dynamic_cast<SerialGroupPathNode*>(path_node); serial_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(serial_group_path_node->getNext(), next_path_node);
                }
                else {
                    serial_group_path_node->setNext(next_path_node);
                }
                break;
            }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const parallel_group_path_node = dynamic_cast<ParallelGroupPathNode*>(path_node); !parallel_group_path_node->getNext().empty()) {
                    for (auto [_, child] : parallel_group_path_node->getNext()) {
                        connectGraphsOfPathNodes(child, next_path_node);
                    }
                }
                else {
                    parallel_group_path_node->setNext(next_path_node->getTopologyElement()->getId(), next_path_node);
                }
                break;
            }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const route_group_path_node = dynamic_cast<RouteGroupPathNode*>(path_node); route_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(route_group_path_node->getNext(), next_path_node);
                }
                else {
                    route_group_path_node->setNext(next_path_node);
                }
                break;
            }

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const open_group_path_node = dynamic_cast<OpenGroupPathNode*>(path_node); open_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(open_group_path_node->getNext(), next_path_node);
                }
                else {
                    open_group_path_node->setNext(next_path_node);
                }
                break;
            }
    }
}

void JobSequenceParser::calculateJobProcessingTimes(Job *job, Topology *topology) {

    for (auto [_, topology_element] : topology->getTopologyElementsMap()) {

        switch (topology_element->getGeneralTopologyElementType()) {

            case ABSTRACT_GENERAL_TOPOLOGY_ELEMENT:
                throw SchedulingError("Abstract topology element encountered in function JobSequenceParser::calculateJobProcessingTimes.");

            case MACHINE_GENERAL_TOPOLOGY_ELEMENT:
                job->addProcessingTime(topology_element->getId(), job->getJobType()->getProcessingTime(dynamic_cast<Machine*>(topology_element)->getMachineType()->getId()));
                break;

            case GROUP_GENERAL_TOPOLOGY_ELEMENT:
                job->addProcessingTime(topology_element->getId(), 0);
                break;
        }
    }
}