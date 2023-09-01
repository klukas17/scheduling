//
// Created by mihael on 29/04/23.
//

/**
 * @file Topology.h
 * @brief Defines the Topology class for representing a topology.
 */

#ifndef SCHEDULING_TOPOLOGY_H
#define SCHEDULING_TOPOLOGY_H

#include "TopologyElement.h"
#include "PathNode.h"
#include <map>

/**
 * @class Topology
 * @brief Represents a topology.
 *
 * The Topology class represents a topology and contains a root element that serves as the starting point of the topology.
 * It provides methods to access topology elements and priority values within the topology.
 */
class Topology {
private:
    TopologyElement* topology_root_element; /**< The root element of the topology. */
    std::map<long, TopologyElement*> topology_elements_map; /**< Map of topology elements indexed by ID. */
    std::map<long, std::map<long, long>> priority_map; /**< Map of priority values indexed by machine IDs. */
public:
    /**
     * @brief Constructs a Topology object with the given root element.
     * @param topology_root_element The root element of the topology.
     */
    explicit Topology(TopologyElement* topology_root_element);

    /**
     * @brief Retrieves the root element of the topology.
     * @return A pointer to the root element of the topology.
     */
    TopologyElement* getRootElement();

    /**
     * @brief Retrieves the map of topology elements indexed by their IDs.
     * @return A map containing pointers to topology elements, indexed by their unique IDs.
     */
    std::map<long, TopologyElement*> getTopologyElementsMap();

    /**
     * @brief Indexes topology elements and path nodes for efficient access.
     * @param node The topology element to index.
     */
    void indexTopologyElements(TopologyElement* node);

    /**
     * @brief Builds the priority map for machines within the topology.
     */
    void buildPriorityMap();

    /**
     * @brief Retrieves the priority value between two machines.
     * @param machine_id_1 The ID of the first machine.
     * @param machine_id_2 The ID of the second machine.
     * @return The priority value between the specified machines.
     */
    long getPriorityValue(long machine_id_1, long machine_id_2);
};

#endif //SCHEDULING_TOPOLOGY_H
