//
// Created by mihael on 8/20/23.
//

/**
 * @file OpenGroupJobPathNode.h
 * @brief Defines the OpenGroupJobPathNode class for representing an open group-related job path node.
 */

#ifndef SCHEDULING_OPENGROUPJOBPATHNODE_H
#define SCHEDULING_OPENGROUPJOBPATHNODE_H

#include "GroupJobPathNode.h"

/**
 * @class OpenGroupJobPathNode
 * @brief Represents an open group-related job path node.
 *
 * The OpenGroupJobPathNode class is derived from the GroupJobPathNode class and represents a node in a job's path
 * that is part of an open group. It inherits attributes and functions from its base class and can include additional
 * open group-specific attributes.
 */
class OpenGroupJobPathNode : public GroupJobPathNode {
private:
    JobPathNode* next; /**< A pointer to the next JobPathNode in the job's path. */
    std::map<long, JobPathNode*> job_sub_path_nodes; /**< A map of job sub-path nodes with corresponding IDs. */
public:
    /**
     * @brief Constructs an OpenGroupJobPathNode object with the given path node.
     * @param path_node A pointer to the underlying PathNode object.
     */
    explicit OpenGroupJobPathNode(PathNode* path_node);

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

    /**
     * @brief Retrieves the map of job sub-path nodes with corresponding IDs.
     * @return A map containing pointers to job sub-path nodes.
     */
    std::map<long, JobPathNode*> getJobSubPathNodes();

    /**
     * @brief Adds a job sub-path node with the specified ID.
     * @param id The ID for the job sub-path node.
     * @param job_path_node A pointer to the job sub-path node to be added.
     */
    void addJobSubPathNode(long id, JobPathNode* job_path_node);
};

#endif //SCHEDULING_OPENGROUPJOBPATHNODE_H

