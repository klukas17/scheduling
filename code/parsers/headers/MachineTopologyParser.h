//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineTopologyParser.h
 * @brief Defines the MachineTopologyParser class for parsing machine topologies from a file.
 */

#ifndef SCHEDULING_MACHINETOPOLOGYPARSER_H
#define SCHEDULING_MACHINETOPOLOGYPARSER_H

#include "Topology.h"
#include "string"
#include "map"
#include "MachineType.h"
#include "MachineTypeMap.h"
#include "yaml-cpp/yaml.h"
#include "set"

/**
 * @class MachineTopologyParser
 * @brief Parses machine topologies.
 *
 * The MachineTopologyParser class provides methods to parse machine topologies and create a Topology object.
 */
class MachineTopologyParser {
public:
    /**
     * @brief Constructs a MachineTopologyParser object.
     */
    MachineTopologyParser();

    /**
     * @brief Parses a machine topology file and creates a Topology object.
     * @param path The path to the machine topology file.
     * @param machine_type_map A pointer to the MachineTypeMap object for mapping machine types.
     * @return A pointer to the Topology object representing the parsed machine topology.
     * @throws SchedulingError if the 'topology' node is not found in the file.
     */
    static Topology* parse(const std::string& path, MachineTypeMap* machine_type_map);

    /**
     * @brief Parses a YAML node representing a topology element and returns the corresponding TopologyElement object.
     * @param path The path to the machine topology file.
     * @param node The YAML node representing the topology element.
     * @param machine_type_map A pointer to the MachineTypeMap object for mapping machine types.
     * @param predecessor_ids A set of predecessor element IDs.
     * @param successor_ids A set of successor element IDs.
     * @return A pointer to the parsed TopologyElement object.
     * @throws SchedulingError if any required keys are missing or if an invalid key is encountered.
     */
    static TopologyElement* parseElement(const std::string& path, const YAML::Node& node, MachineTypeMap* machine_type_map, std::set<long>& predecessor_ids, std::set<long>& successor_ids);
};

#endif // SCHEDULING_MACHINETOPOLOGYPARSER_H

