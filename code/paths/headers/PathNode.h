//
// Created by mihael on 29/06/23.
//

/**
 * @file PathNode.h
 * @brief Defines the PathNode class for representing nodes in a path through a topology.
 */

#ifndef SCHEDULING_PATHNODE_H
#define SCHEDULING_PATHNODE_H

#include "vector"
#include "map"
#include "TopologyElement.h"
#include "Prerequisite.h"

/**
 * @class PathNode
 * @brief Represents nodes in a path through a topology.
 *
 * The PathNode class represents nodes that form a path through a topology. Each node is associated with a topology element
 * and may have prerequisites. It provides methods to access and manipulate these attributes.
 */
class PathNode {
protected:
    long path_node_id;
    TopologyElement* topology_element; /**< Pointer to the associated topology element. */
    std::vector<Prerequisite*> prerequisites; /**< Vector of prerequisites associated with this node. */
public:
    /**
     * @brief Constructs a PathNode object associated with the provided topology element.
     * @param topology_element A pointer to the associated topology element.
     */
    PathNode(long path_node_id, TopologyElement* topology_element);

    /**
     * @brief Virtual destructor for PathNode.
     *
     * This is a virtual destructor for the PathNode class to allow for proper destruction of derived classes.
     */
    virtual ~PathNode() = 0;

    long getPathNodeId();

    /**
     * @brief Retrieves the associated topology element.
     * @return A pointer to the associated TopologyElement.
     */
    TopologyElement* getTopologyElement();

    /**
     * @brief Retrieves the vector of prerequisites associated with this node.
     * @return A vector containing pointers to the associated Prerequisite objects.
     */
    std::vector<Prerequisite*> getPrerequisites();

    /**
     * @brief Adds a prerequisite to this path node.
     * @param prerequisite A pointer to the Prerequisite to be added.
     */
    void addPrerequisite(Prerequisite* prerequisite);

    /**
     * @brief Deletes this path node.
     *
     * This function deletes the current path node, including its associated topology element and prerequisites.
     */
    void deletePathNode();

    /**
     * @brief Finds sub-path nodes connected to this path node.
     *
     * This function recursively finds sub-path nodes connected to this path node and adds them to the provided set.
     *
     * @param current_node A pointer to the current path node being examined.
     * @param sub_path_nodes A set to which sub-path nodes will be added.
     */
    void findSubPathNodes(PathNode* current_node, std::set<PathNode*>& sub_path_nodes);
};

#endif //SCHEDULING_PATHNODE_H
