//
// Created by mihael on 8/20/23.
//

/**
 * @file RouteGroupJobPathNode.h
 * @brief Defines the RouteGroupJobPathNode class for representing a route group-related job path node.
 */

#ifndef SCHEDULING_ROUTEGROUPJOBPATHNODE_H
#define SCHEDULING_ROUTEGROUPJOBPATHNODE_H

#include "GroupJobPathNode.h"

/**
 * @class RouteGroupJobPathNode
 * @brief Represents a route group-related job path node.
 *
 * The RouteGroupJobPathNode class is derived from the GroupJobPathNode class and represents a node in a job's path
 * that is part of a route group. It inherits attributes and functions from its base class and can include additional
 * route group-specific attributes.
 */
class RouteGroupJobPathNode : public GroupJobPathNode {
private:
    JobPathNode* next; /**< A pointer to the next JobPathNode in the job's path. */
public:
    /**
     * @brief Constructs a RouteGroupJobPathNode object with the given path node.
     * @param path_node A pointer to the underlying PathNode object.
     */
    explicit RouteGroupJobPathNode(PathNode* path_node);

    /**
     * @brief Retrieves the pointer to the next JobPathNode in the job's path.
     * @return A pointer to the next JobPathNode.
     */
    JobPathNode* getNext();

    /**
     * @brief Sets the pointer to the next JobPathNode in the job's path.
     * @param job_path_node A pointer to the next JobPathNode to set.
     */
    void setNext(JobPathNode* job_path_node);
};

#endif //SCHEDULING_ROUTEGROUPJOBPATHNODE_H

