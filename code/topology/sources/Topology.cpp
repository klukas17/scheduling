//
// Created by mihael on 29/04/23.
//

/**
 * @file Topology.cpp
 * @brief Implements the member functions of the Topology class.
 */

#include "Topology.h"

Topology::Topology(TopologyElement* topology_root_element) {
    this->topology_root_element = topology_root_element;
}

TopologyElement* Topology::getRootElement() {
    return topology_root_element;
}
