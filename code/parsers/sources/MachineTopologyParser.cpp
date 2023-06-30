//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineTopologyParser.cpp
 * @brief Implements the member functions of the MachineTopologyParser class.
 */

#include "MachineTopologyParser.h"
#include "Machine.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "OpenGroup.h"
#include "SchedulingError.h"

MachineTopologyParser::MachineTopologyParser() = default;

Topology *MachineTopologyParser::parse(const std::string& path, MachineTypeMap* machine_type_map) {

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node topology_node = doc["topology"];

    if (topology_node) {
        std::set<long> predecessor_ids, successor_ids;
        TopologyElement* topology_element = parseElement(path, topology_node, machine_type_map, predecessor_ids, successor_ids);
        auto topology = new Topology(topology_element);

        return topology;
    }
    else {
        throw SchedulingError("'topology' node not found in file " + path);
    }
}

TopologyElement *MachineTopologyParser::parseElement(const std::string& path, const YAML::Node& node, MachineTypeMap* machine_type_map, std::set<long>& predecessor_ids, std::set<long>& successor_ids) {

    if (node["machine"]) {
        YAML::Node machine_node = node["machine"];
        if (!machine_node["id"]) {
            throw SchedulingError("'machine' node must have an 'id' key");
        }
        long id = machine_node["id"].as<long>();
        MachineType* machine_type = machine_type_map->getMachineType(id);
        auto topology_element = new Machine(id, machine_type);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);
        return topology_element;
    }

    else if (node["serial"]) {
        YAML::Node serial_node = node["serial"];
        if (!serial_node["id"]) {
            throw SchedulingError("'serial' node must have an 'id' key");
        }
        long id = serial_node["id"].as<long>();
        auto topology_element = new SerialGroup(id);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set<long> children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        YAML::Node body_node = serial_node["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(path, *it, machine_type_map, children_predecessor_ids, child_successor_ids);
                topology_element->addChild(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                    children_predecessor_ids.insert(successor_id);
                }
            }
        }
        else {
            throw SchedulingError("'serial' node must have a 'body' key");
        }
        return topology_element;
    }

    else if (node["parallel"]) {
        YAML::Node parallel_node = node["parallel"];
        if (!parallel_node["id"]) {
            throw SchedulingError("'parallel' node must have an 'id' key");
        }
        long id = parallel_node["id"].as<long>();
        auto topology_element = new ParallelGroup(id);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set<long> children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        YAML::Node body_node = parallel_node["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(path, *it, machine_type_map, children_predecessor_ids, child_successor_ids);
                topology_element->addChild(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            throw SchedulingError("'parallel' node must have a 'body' key");
        }
        return topology_element;
    }

    else if (node["route"]) {
        YAML::Node route_node = node["route"];
        if (!route_node["id"]) {
            throw SchedulingError("'route' node must have an 'id' key");
        }
        long id = route_node["id"].as<long>();
        auto topology_element = new RouteGroup(id);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set<long> children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        YAML::Node body_node = route_node["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(path, *it, machine_type_map, children_predecessor_ids, child_successor_ids);
                topology_element->addChild(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            throw SchedulingError("'route' node must have a 'body' key");
        }
        return topology_element;
    }

    else if (node["open"]) {
        YAML::Node open_node = node["open"];
        if (!open_node["id"]) {
            throw SchedulingError("'open' node must have an 'id' key");
        }
        long id = open_node["id"].as<long>();
        auto topology_element = new OpenGroup(id);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set<long> children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        YAML::Node body_node = open_node["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(path, *it, machine_type_map, children_predecessor_ids, child_successor_ids);
                topology_element->addChild(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            throw SchedulingError("'open' node must have a 'body' key");
        }
        return topology_element;
    }

    else {
        throw SchedulingError("Key can only be machine, serial, parallel, route or open in file " + path);
    }
}