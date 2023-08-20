//
// Created by mihael on 8/20/23.
//
/**
 * @file MachineJobPathNode.h
 * @brief Defines the MachineJobPathNode class for representing a machine-related job path node.
 */

#ifndef SCHEDULING_MACHINEJOBPATHNODE_H
#define SCHEDULING_MACHINEJOBPATHNODE_H

#include "JobPathNode.h"

/**
 * @class MachineJobPathNode
 * @brief Represents a machine-related job path node.
 *
 * The MachineJobPathNode class is derived from the JobPathNode class and represents a node in a job's path that is
 * related to a specific machine. It inherits attributes and functions from its base class and can include additional
 * machine-specific attributes.
 */
class MachineJobPathNode : public JobPathNode {
private:
    JobPathNode* next; /**< A pointer to the next JobPathNode in the job's path. */
public:
    /**
     * @brief Constructs a MachineJobPathNode object with the given path node.
     * @param path_node A pointer to the underlying PathNode object.
     */
    MachineJobPathNode(PathNode* path_node);

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

#endif //SCHEDULING_MACHINEJOBPATHNODE_H

