//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "MachineTopologyParser.h"
#include "Machine.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "OpenGroup.h"

MachineTopologyParser::MachineTopologyParser() = default;

Topology *MachineTopologyParser::parse(const std::string& path, const std::map<long, MachineType *>& machine_type_map) {

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node topology_node = doc["topology"];

    if (topology_node) {

        std::set<long> predecessor_ids, successor_ids;
        TopologyElement* topology_element = parseElement(topology_node, machine_type_map, predecessor_ids, successor_ids);
        auto topology = new Topology(topology_element);

        return topology;
    }

    else {
        // todo:error
        std::cerr << "Error: 'topology' node not found in " << path << " file." << std::endl;
        exit(1);
    }
}

TopologyElement *MachineTopologyParser::parseElement(const YAML::Node& node, const std::map<long, MachineType*>& machine_type_map, std::set<long>& predecessor_ids, std::set<long>& successor_ids) {

    if (node["machine"]) {
        long id = node["machine"]["id"].as<long>();
        MachineType* machine_type = machine_type_map.find(node["machine"]["machine_type_id"].as<long>())->second;
        auto topology_element = new Machine(id, machine_type);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);
        return topology_element;
    }

    else if (node["serial"]) {
        long id = node["serial"]["id"].as<long>();
        auto topology_element = new SerialGroup(id);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set<long> children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        YAML::Node body_node = node["serial"]["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(*it, machine_type_map, children_predecessor_ids, child_successor_ids);
                topology_element->addElementToBody(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                    children_predecessor_ids.insert(successor_id);
                }
            }
        }
        else {
            // todo:error
        }
        return topology_element;
    }

    else if (node["parallel"]) {
        long id = node["parallel"]["id"].as<long>();
        auto topology_element = new ParallelGroup(id);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set<long> children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        YAML::Node body_node = node["parallel"]["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(*it, machine_type_map, children_predecessor_ids, child_successor_ids);
                topology_element->addElementToBody(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            // todo:error
        }
        return topology_element;
    }

    else if (node["route"]) {
        long id = node["route"]["id"].as<long>();
        auto topology_element = new RouteGroup(id);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set<long> children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        YAML::Node body_node = node["route"]["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(*it, machine_type_map, children_predecessor_ids, child_successor_ids);
                topology_element->addElementToBody(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            // todo:error
        }
        return topology_element;
    }

    else if (node["open"]) {
        long id = node["open"]["id"].as<long>();
        auto topology_element = new OpenGroup(id);
        for (auto predecessor_id : predecessor_ids) {
            topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set<long> children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        YAML::Node body_node = node["open"]["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(*it, machine_type_map, children_predecessor_ids, child_successor_ids);
                topology_element->addElementToBody(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            // todo:error
        }
        return topology_element;
    }

    else {
        // todo:error
    }
}