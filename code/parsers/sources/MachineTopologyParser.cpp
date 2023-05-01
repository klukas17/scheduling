//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "MachineTopologyParser.h"
#include "Machine.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"

MachineTopologyParser::MachineTopologyParser() = default;

Topology *MachineTopologyParser::parse(const std::string& path, const std::map<long, MachineType *>& machine_type_map) {

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node topology_node = doc["topology"];

    if (topology_node) {

        TopologyElement* topology_element = parseElement(topology_node, machine_type_map);
        auto topology = new Topology(topology_element);

        return topology;
    }

    else {
        // todo:error
        std::cerr << "Error: 'topology' node not found in " << path << " file." << std::endl;
        exit(1);
    }
}

TopologyElement *MachineTopologyParser::parseElement(const YAML::Node& node, const std::map<long, MachineType*>& machine_type_map) {

    if (node["machine"]) {
        long id = node["machine"]["id"].as<long>();
        MachineType* machine_type = machine_type_map.find(node["machine"]["machine_type_id"].as<long>())->second;
        auto topology_element = new Machine(id, machine_type);
        return topology_element;
    }

    else if (node["serial"]) {
        long id = node["serial"]["id"].as<long>();
        auto topology_element = new SerialGroup(id);

        YAML::Node body_node = node["serial"]["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                TopologyElement* child_element = parseElement(*it, machine_type_map);
                topology_element->addElementToBody(child_element);
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

        YAML::Node body_node = node["parallel"]["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                TopologyElement* child_element = parseElement(*it, machine_type_map);
                topology_element->addElementToBody(child_element);
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

        YAML::Node body_node = node["route"]["body"];
        if (body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); it++) {
                TopologyElement* child_element = parseElement(*it, machine_type_map);
                topology_element->addElementToBody(child_element);
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