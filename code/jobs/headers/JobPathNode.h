//
// Created by mihael on 29/06/23.
//

/**
 * @file JobPathNode.h
 * @brief Defines the JobPathNode class for representing a node in a job path.
 */

#ifndef SCHEDULING_JOBPATHNODE_H
#define SCHEDULING_JOBPATHNODE_H

#include "vector"
#include "map"
#include "PathNode.h"
#include "Prerequisite.h"

/**
 * @class JobPathNode
 * @brief Represents a node in a job path.
 *
 * The JobPathNode class serves as a base class for representing a node in a job's path. It encapsulates information
 * about a path node and associated prerequisites. Derived classes can extend this class to include specific attributes.
 */
class JobPathNode {
protected:
    PathNode* path_node; /**< A pointer to the underlying PathNode object representing this job path node. */
    std::vector<Prerequisite*> prerequisites; /**< A vector of prerequisites associated with this job path node. */
public:
    /**
     * @brief Constructs a JobPathNode object with the given path node.
     * @param path_node A pointer to the underlying PathNode object.
     */
    explicit JobPathNode(PathNode* path_node);

    /**
     * @brief Virtual destructor for proper inheritance.
     *
     * This virtual destructor ensures proper cleanup when inheriting from this base class.
     */
    virtual ~JobPathNode() = 0;

    /**
     * @brief Retrieves the underlying PathNode object of this job path node.
     * @return A pointer to the PathNode object.
     */
    PathNode* getPathNode();

    /**
     * @brief Retrieves the vector of prerequisites associated with this job path node.
     * @return A vector containing pointers to Prerequisite objects.
     */
    std::vector<Prerequisite*> getPrerequisites();

    /**
     * @brief Adds a prerequisite to this job path node.
     * @param prerequisite A pointer to the Prerequisite object to be added.
     */
    void addPrerequisite(Prerequisite* prerequisite);
};

#endif //SCHEDULING_JOBPATHNODE_H

