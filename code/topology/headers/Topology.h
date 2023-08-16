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
 */
class Topology {
private:
    TopologyElement* topology_root_element; /**< The root element of the topology. */
    PathNode* root_path_node; /**< The root node of the structure containing all paths through the topology. */
    std::map<long, TopologyElement*> topology_elements_map; /**< Map of topology elements indexed by ID. */
    std::map<long, PathNode*> path_nodes_map; /**< Map of path nodes indexed by ID. */
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
     * @brief Retrieves the  root node of the structure containing all paths through the topology.
     * @return A pointer to the root node of the structure containing all paths through the topology.
     */
    PathNode* getRootPathNode();

    /**
     * @brief Retrieves the map of topology elements indexed by their IDs.
     * @return A map containing pointers to topology elements, indexed by their unique IDs.
     */
    std::map<long, TopologyElement*> getTopologyElementsMap();

    /**
     * @brief Retrieves the map of path nodes indexed by their IDs.
     * @return A map containing pointers to path nodes, indexed by their unique IDs.
     */
    std::map<long, PathNode*> getPathNodesMap();

    /**
     * @brief Indexes topology elements and path nodes for efficient access.
     * @param node The topology element to index.
     */
    void indexTopologyElementsAndPathNodes(TopologyElement* node);

    /**
     * @brief Builds paths within the topology.
     * @param topology_element The topology element for which to build paths.
     * @param node The path node for which to build paths.
     * @param next The next path node to connect the current node to.
     */
    void buildPaths(TopologyElement* topology_element, PathNode* node, PathNode* next);
};

#endif //SCHEDULING_TOPOLOGY_H
