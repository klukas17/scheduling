//
// Created by mihael on 8/20/23.
//

/**
 * @file GroupJobPathNode.h
 * @brief Defines the GroupJobPathNode class for representing a group job path node.
 */

#ifndef SCHEDULING_GROUPJOBPATHNODE_H
#define SCHEDULING_GROUPJOBPATHNODE_H

#include "JobPathNode.h"

/**
 * @class GroupJobPathNode
 * @brief Represents a group job path node.
 *
 * The GroupJobPathNode class is derived from the JobPathNode class and represents a node in a job's path that is part
 * of a group. It inherits attributes and functions from its base class and can include additional specific attributes.
 */
class GroupJobPathNode : public JobPathNode {
public:
    /**
     * @brief Constructs a GroupJobPathNode object with the given path node.
     * @param path_node A pointer to the underlying PathNode object.
     */
    explicit GroupJobPathNode(PathNode* path_node);

    /**
     * @brief Virtual destructor for proper inheritance.
     *
     * This virtual destructor ensures proper cleanup when inheriting from this base class.
     */
    ~GroupJobPathNode() override = 0;
};

#endif //SCHEDULING_GROUPJOBPATHNODE_H

