//
// Created by mihael on 8/20/23.
//

/**
 * @file ParallelGroupJobPathNode.h
 * @brief Defines the ParallelGroupJobPathNode class for representing a parallel group-related job path node.
 */

#ifndef SCHEDULING_PARALLELGROUPJOBPATHNODE_H
#define SCHEDULING_PARALLELGROUPJOBPATHNODE_H

#include "GroupJobPathNode.h"

/**
 * @class ParallelGroupJobPathNode
 * @brief Represents a parallel group-related job path node.
 *
 * The ParallelGroupJobPathNode class is derived from the GroupJobPathNode class and represents a node in a job's path
 * that is part of a parallel group. It inherits attributes and functions from its base class and can include additional
 * parallel group-specific attributes.
 */
class ParallelGroupJobPathNode : public GroupJobPathNode {
private:
    std::map<long, JobPathNode*> next; /**< A map of next JobPathNodes in the job's path with corresponding IDs. */
public:
    /**
     * @brief Constructs a ParallelGroupJobPathNode object with the given path node.
     * @param path_node A pointer to the underlying PathNode object.
     */
    explicit ParallelGroupJobPathNode(PathNode* path_node);

    /**
     * @brief Retrieves the map of next JobPathNodes in the job's path with corresponding IDs.
     * @return A map containing pointers to the next JobPathNodes.
     */
    std::map<long, JobPathNode*> getNext();

    /**
     * @brief Sets the next JobPathNode for a specific ID in the job's path.
     * @param id The ID for which to set the next JobPathNode.
     * @param job_path_node A pointer to the next JobPathNode to set.
     */
    void setNext(long id, JobPathNode* job_path_node);
};

#endif //SCHEDULING_PARALLELGROUPJOBPATHNODE_H

