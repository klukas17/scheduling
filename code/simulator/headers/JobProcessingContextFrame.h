//
// Created by mihael on 9/14/23.
//

/**
 * @file JobProcessingContextFrame.h
 * @brief Defines the JobProcessingContextFrame class for representing a frame related to open open machines in a job processing context.
 */

#ifndef SCHEDULING_JOBPROCESSINGCONTEXTFRAME_H
#define SCHEDULING_JOBPROCESSINGCONTEXTFRAME_H

#include "OpenGroupPathTreeNode.h"
#include "map"

/**
 * @class JobProcessingContextFrame
 * @brief Represents a context frame for job processing within a path tree node.
 *
 * The JobProcessingContextFrame class encapsulates information related to the processing context of a job
 * within a path tree node. It is used to track the open group path tree node and the visited status of its children.
 */
class JobProcessingContextFrame {
private:
    OpenGroupPathTreeNode* open_group_path_tree_node; /**< A pointer to the open group path tree node in the context. */
    std::map<long, bool> children_visited; /**< A map to track the visited status of children path nodes. */

public:
    /**
     * @brief Constructs a JobProcessingContextFrame object with the specified open group path tree node.
     * @param open_group_path_tree_node A pointer to the open group path tree node in the context.
     */
    explicit JobProcessingContextFrame(OpenGroupPathTreeNode* open_group_path_tree_node);

    /**
     * @brief Retrieves the open group path tree node in the processing context.
     * @return A pointer to the open group path tree node.
     */
    OpenGroupPathTreeNode* getOpenGroupPathTreeNode();

    /**
     * @brief Marks a child path node as visited within the context.
     * @param path_node_id The identifier of the child path node to mark as visited.
     */
    void visitChild(long path_node_id);

    /**
     * @brief Checks if all children of the open group path tree node have been visited.
     * @return `true` if all children have been visited, `false` otherwise.
     */
    bool checkAllChildrenVisited();
};

#endif //SCHEDULING_JOBPROCESSINGCONTEXTFRAME_H

