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

/**
 * @class Topology
 * @brief Represents a topology.
 *
 * The Topology class represents a topology and contains a root element that serves as the starting point of the topology.
 */
class Topology {
private:
    TopologyElement* topology_root_element; /**< The root element of the topology. */
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
};

#endif //SCHEDULING_TOPOLOGY_H
