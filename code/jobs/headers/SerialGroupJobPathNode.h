//
// Created by mihael on 8/20/23.
//

/**
 * @file SerialGroupJobPathNode.h
 * @brief Defines the SerialGroupJobPathNode class for representing a serial group-related job path node.
 */

#ifndef SCHEDULING_SERIALGROUPJOBPATHNODE_H
#define SCHEDULING_SERIALGROUPJOBPATHNODE_H

#include "GroupJobPathNode.h"

/**
 * @class SerialGroupJobPathNode
 * @brief Represents a serial group-related job path node.
 *
 * The SerialGroupJobPathNode class is derived from the GroupJobPathNode class and represents a node in a job's path
 * that is part of a serial group. It inherits attributes and functions from its base class and can include additional
 * serial group-specific attributes.
 */
class SerialGroupJobPathNode : public GroupJobPathNode {
private:
    JobPathNode* next; /**< A pointer to the next JobPathNode in the job's path. */
public:
    /**
     * @brief Constructs a SerialGroupJobPathNode object with the given path node.
     * @param path_node A pointer to the underlying PathNode object.
     */
    explicit SerialGroupJobPathNode(PathNode* path_node);

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

#endif //SCHEDULING_SERIALGROUPJOBPATHNODE_H

