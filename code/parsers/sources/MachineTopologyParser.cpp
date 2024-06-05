//
// Created by mihael on 29/04/23.
//

#include "MachineTopologyParser.h"
#include "Machine.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "OpenGroup.h"
#include "SchedulingError.h"
#include <climits>

Topology *MachineTopologyParser::parse(const std::string& path, MachineTypeMap* machine_type_map) {

    YAML::Node doc = YAML::LoadFile(path);

    if (YAML::Node const topology_node = doc["topology"]; topology_node) {
        std::set<long> predecessor_ids, successor_ids;
        TopologyElement* topology_element = parseElement(path, topology_node, machine_type_map, predecessor_ids, successor_ids);
        auto const topology = new Topology(topology_element);

        return topology;
    }

    throw SchedulingError("'topology' node not found in file " + path);
}

TopologyElement *MachineTopologyParser::parseElement(const std::string& path, const YAML::Node& node, MachineTypeMap* machine_type_map, std::set<long>& predecessor_ids, std::set<long>& successor_ids) {

    TopologyElement* topology_element;

    if (node["machine"]) {
        YAML::Node machine_node = node["machine"];
        if (!machine_node["id"]) {
            throw SchedulingError("'machine' node must have an 'id' key");
        }
        long id = machine_node["id"].as<long>();
        if (!machine_node["machine_type_id"]) {
            throw SchedulingError("'machine' node must have a 'machine_type_id' key");
        }
        long machine_type_id = machine_node["machine_type_id"].as<long>();
        long buffer_size = machine_node["buffer_size"] ? machine_node["buffer_size"].as<long>() : LONG_MAX;
        if (buffer_size < 1) {
            throw SchedulingError("Buffer with size smaller than 1 found in MachineTopologyParser::parseElement function.");
        }
        MachineType* machine_type = machine_type_map->getMachineType(machine_type_id);
        auto machine_topology_element = new Machine(id, machine_type);
        machine_topology_element->setBufferSize(buffer_size);
        topology_element = machine_topology_element;
        for (auto predecessor_id : predecessor_ids) {
            machine_topology_element->addPredecessorId(predecessor_id);
        }
        if (const YAML::Node& breakdowns_node = machine_node["breakdowns"]; breakdowns_node) {
            for (auto breakdown_it = breakdowns_node.begin(); breakdown_it != breakdowns_node.end(); ++breakdown_it) {
                if (!(*breakdown_it)["start_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array must contain 'start_time' field in the file " + path);
                }
                auto start_time = (*breakdown_it)["start_time"].as<double>();
                if (!(*breakdown_it)["end_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array array must contain 'end_time' field in the file " + path);
                }
                auto end_time = (*breakdown_it)["end_time"].as<double>();
                if (start_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' lower than 0 in the file " + path);
                }
                if (end_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'end_time' lower than 0 in the file " + path);
                }
                if (end_time < start_time) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' larger than 'end_time' in the file " + path);
                }
                for (auto breakdown : topology_element->getBreakdowns()) {
                    if (double const breakdown_start_time = breakdown->getStartTime(), breakdown_end_time = breakdown->getEndTime(); start_time != end_time && breakdown_start_time != breakdown_end_time && (start_time >= breakdown_start_time && start_time < breakdown_end_time || end_time > breakdown_start_time && end_time <= breakdown_end_time)) {
                        throw SchedulingError("Entries in the 'breakdowns' array overlap in the file " + path);
                    }
                }
                topology_element->addBreakdown(new Breakdown(start_time, end_time));
            }
        }
        successor_ids.insert(id);
    }

    else if (node["serial"]) {
        YAML::Node serial_node = node["serial"];
        if (!serial_node["id"]) {
            throw SchedulingError("'serial' node must have an 'id' key");
        }
        long id = serial_node["id"].as<long>();
        long buffer_size = serial_node["buffer_size"] ? serial_node["buffer_size"].as<long>() : LONG_MAX;
        if (buffer_size < 1) {
            throw SchedulingError("Buffer with size smaller than 1 found in MachineTopologyParser::parseElement function.");
        }
        auto serial_group_topology_element = new SerialGroup(id);
        serial_group_topology_element->setBufferSize(buffer_size);
        topology_element = serial_group_topology_element;
        for (auto predecessor_id : predecessor_ids) {
            serial_group_topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        if (YAML::Node body_node = serial_node["body"]; body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); ++it) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(path, *it, machine_type_map, children_predecessor_ids, child_successor_ids);
                serial_group_topology_element->addChild(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                    children_predecessor_ids.insert(successor_id);
                }
            }
        }
        else {
            throw SchedulingError("'serial' node must have a 'body' key");
        }

        if (const YAML::Node& breakdowns_node = serial_node["breakdowns"]; breakdowns_node) {
            for (auto breakdown_it = breakdowns_node.begin(); breakdown_it != breakdowns_node.end(); ++breakdown_it) {
                if (!(*breakdown_it)["start_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array must contain 'start_time' field in the file " + path);
                }
                auto start_time = (*breakdown_it)["start_time"].as<double>();
                if (!(*breakdown_it)["end_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array array must contain 'end_time' field in the file " + path);
                }
                auto end_time = (*breakdown_it)["end_time"].as<double>();
                if (start_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' lower than 0 in the file " + path);
                }
                if (end_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'end_time' lower than 0 in the file " + path);
                }
                if (end_time < start_time) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' larger than 'end_time' in the file " + path);
                }
                for (auto breakdown : topology_element->getBreakdowns()) {
                    if (double const breakdown_start_time = breakdown->getStartTime(), breakdown_end_time = breakdown->getEndTime(); start_time != end_time && breakdown_start_time != breakdown_end_time && (start_time >= breakdown_start_time && start_time < breakdown_end_time || end_time > breakdown_start_time && end_time <= breakdown_end_time)) {
                        throw SchedulingError("Entries in the 'breakdowns' array overlap in the file " + path);
                    }
                }
                topology_element->addBreakdown(new Breakdown(start_time, end_time));
            }
        }
    }

    else if (node["parallel"]) {
        YAML::Node parallel_node = node["parallel"];
        if (!parallel_node["id"]) {
            throw SchedulingError("'parallel' node must have an 'id' key");
        }
        long id = parallel_node["id"].as<long>();
        long buffer_size = parallel_node["buffer_size"] ? parallel_node["buffer_size"].as<long>() : LONG_MAX;
        if (buffer_size < 1) {
            throw SchedulingError("Buffer with size smaller than 1 found in MachineTopologyParser::parseElement function.");
        }
        auto parallel_group_topology_element = new ParallelGroup(id);
        parallel_group_topology_element->setBufferSize(buffer_size);
        topology_element = parallel_group_topology_element;
        for (auto predecessor_id : predecessor_ids) {
            parallel_group_topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        if (YAML::Node body_node = parallel_node["body"]; body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); ++it) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(path, *it, machine_type_map, children_predecessor_ids, child_successor_ids);
                parallel_group_topology_element->addChild(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            throw SchedulingError("'parallel' node must have a 'body' key");
        }

        if (const YAML::Node& breakdowns_node = parallel_node["breakdowns"]; breakdowns_node) {
            for (auto breakdown_it = breakdowns_node.begin(); breakdown_it != breakdowns_node.end(); ++breakdown_it) {
                if (!(*breakdown_it)["start_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array must contain 'start_time' field in the file " + path);
                }
                auto const start_time = (*breakdown_it)["start_time"].as<double>();
                if (!(*breakdown_it)["end_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array array must contain 'end_time' field in the file " + path);
                }
                auto const end_time = (*breakdown_it)["end_time"].as<double>();
                if (start_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' lower than 0 in the file " + path);
                }
                if (end_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'end_time' lower than 0 in the file " + path);
                }
                if (end_time < start_time) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' larger than 'end_time' in the file " + path);
                }
                for (auto breakdown : topology_element->getBreakdowns()) {
                    if (auto const breakdown_start_time = breakdown->getStartTime(), breakdown_end_time = breakdown->getEndTime(); start_time != end_time && breakdown_start_time != breakdown_end_time && (start_time >= breakdown_start_time && start_time < breakdown_end_time || end_time > breakdown_start_time && end_time <= breakdown_end_time)) {
                        throw SchedulingError("Entries in the 'breakdowns' array overlap in the file " + path);
                    }
                }
                topology_element->addBreakdown(new Breakdown(start_time, end_time));
            }
        }
    }

    else if (node["route"]) {
        YAML::Node route_node = node["route"];
        if (!route_node["id"]) {
            throw SchedulingError("'route' node must have an 'id' key");
        }
        long id = route_node["id"].as<long>();
        long buffer_size = route_node["buffer_size"] ? route_node["buffer_size"].as<long>() : LONG_MAX;
        if (buffer_size < 1) {
            throw SchedulingError("Buffer with size smaller than 1 found in MachineTopologyParser::parseElement function.");
        }
        auto route_group_topology_element = new RouteGroup(id);
        route_group_topology_element->setBufferSize(buffer_size);
        topology_element = route_group_topology_element;
        for (auto predecessor_id : predecessor_ids) {
            route_group_topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        if (YAML::Node body_node = route_node["body"]; body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); ++it) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(path, *it, machine_type_map, children_predecessor_ids, child_successor_ids);
                route_group_topology_element->addChild(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            throw SchedulingError("'route' node must have a 'body' key");
        }

        if (const YAML::Node& breakdowns_node = route_node["breakdowns"]; breakdowns_node) {
            for (auto breakdown_it = breakdowns_node.begin(); breakdown_it != breakdowns_node.end(); ++breakdown_it) {
                if (!(*breakdown_it)["start_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array must contain 'start_time' field in the file " + path);
                }
                auto const start_time = (*breakdown_it)["start_time"].as<double>();
                if (!(*breakdown_it)["end_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array array must contain 'end_time' field in the file " + path);
                }
                auto const end_time = (*breakdown_it)["end_time"].as<double>();
                if (start_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' lower than 0 in the file " + path);
                }
                if (end_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'end_time' lower than 0 in the file " + path);
                }
                if (end_time < start_time) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' larger than 'end_time' in the file " + path);
                }
                for (auto breakdown : topology_element->getBreakdowns()) {
                    if (auto const breakdown_start_time = breakdown->getStartTime(), breakdown_end_time = breakdown->getEndTime(); start_time != end_time && breakdown_start_time != breakdown_end_time && (start_time >= breakdown_start_time && start_time < breakdown_end_time || end_time > breakdown_start_time && end_time <= breakdown_end_time)) {
                        throw SchedulingError("Entries in the 'breakdowns' array overlap in the file " + path);
                    }
                }
                topology_element->addBreakdown(new Breakdown(start_time, end_time));
            }
        }
    }

    else if (node["open"]) {
        YAML::Node open_node = node["open"];
        if (!open_node["id"]) {
            throw SchedulingError("'open' node must have an 'id' key");
        }
        long id = open_node["id"].as<long>();
        long buffer_size = open_node["buffer_size"] ? open_node["buffer_size"].as<long>() : LONG_MAX;
        if (buffer_size < 1) {
            throw SchedulingError("Buffer with size smaller than 1 found in MachineTopologyParser::parseElement function.");
        }
        auto open_group_topology_element = new OpenGroup(id);
        open_group_topology_element->setBufferSize(buffer_size);
        topology_element = open_group_topology_element;
        for (auto predecessor_id : predecessor_ids) {
            open_group_topology_element->addPredecessorId(predecessor_id);
        }
        successor_ids.insert(id);

        std::set children_predecessor_ids(predecessor_ids);
        children_predecessor_ids.insert(id);

        if (YAML::Node body_node = open_node["body"]; body_node) {
            for (auto it = body_node.begin(); it != body_node.end(); ++it) {
                std::set<long> child_successor_ids;
                TopologyElement* child_element = parseElement(path, *it, machine_type_map, children_predecessor_ids, child_successor_ids);
                open_group_topology_element->addChild(child_element);
                for (auto successor_id : child_successor_ids) {
                    successor_ids.insert(successor_id);
                }
            }
        }
        else {
            throw SchedulingError("'open' node must have a 'body' key");
        }

        if (const YAML::Node& breakdowns_node = open_node["breakdowns"]; breakdowns_node) {
            for (auto breakdown_it = breakdowns_node.begin(); breakdown_it != breakdowns_node.end(); ++breakdown_it) {
                if (!(*breakdown_it)["start_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array must contain 'start_time' field in the file " + path);
                }
                auto const start_time = (*breakdown_it)["start_time"].as<double>();
                if (!(*breakdown_it)["end_time"]) {
                    throw SchedulingError("Entry in the 'breakdowns' array array must contain 'end_time' field in the file " + path);
                }
                auto const end_time = (*breakdown_it)["end_time"].as<double>();
                if (start_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' lower than 0 in the file " + path);
                }
                if (end_time < 0) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'end_time' lower than 0 in the file " + path);
                }
                if (end_time < start_time) {
                    throw SchedulingError("Entry in the 'breakdowns' array has 'start_time' larger than 'end_time' in the file " + path);
                }
                for (auto breakdown : topology_element->getBreakdowns()) {
                    if (auto const breakdown_start_time = breakdown->getStartTime(), breakdown_end_time = breakdown->getEndTime(); start_time != end_time && breakdown_start_time != breakdown_end_time && (start_time >= breakdown_start_time && start_time < breakdown_end_time || end_time > breakdown_start_time && end_time <= breakdown_end_time)) {
                        throw SchedulingError("Entries in the 'breakdowns' array overlap in the file " + path);
                    }
                }
                topology_element->addBreakdown(new Breakdown(start_time, end_time));
            }
        }
    }

    else {
        throw SchedulingError("Key can only be machine, serial, parallel, route or open in file " + path);
    }

    return topology_element;
}