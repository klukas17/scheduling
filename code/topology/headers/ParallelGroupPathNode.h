//
// Created by mihael on 8/15/23.
//

/**
 * @file ParallelGroupPathNode.h
 * @brief Defines the ParallelGroupPathNode class for representing a parallel group node within a topology path.
 */

#ifndef SCHEDULING_PARALLELGROUPPATHNODE_H
#define SCHEDULING_PARALLELGROUPPATHNODE_H

#include "GroupPathNode.h"
#include <map>

/**
 * @class ParallelGroupPathNode
 * @brief Represents a parallel group node within a topology path.
 *
 * The ParallelGroupPathNode class is a derived class of GroupPathNode, representing a node within a topology path that is specific to a parallel group.
 * It contains information about the associated topology element, its group-specific element types, and a map of pointers to next nodes in the path.
 */
class ParallelGroupPathNode : public GroupPathNode {
private:
    std::map<long, PathNode*> next; /**< A map of pointers to next nodes in the parallel group-specific topology path. */
public:
    /**
     * @brief Constructs a ParallelGroupPathNode object with the given topology element.
     * @param topology_element The associated topology element of the parallel group-specific path node.
     */
    explicit ParallelGroupPathNode(TopologyElement* topology_element);

    /**
     * @brief Retrieves the map of pointers to next nodes in the parallel group-specific topology path.
     * @return A map containing pointers to next nodes in the parallel group-specific topology path, indexed by IDs.
     */
    std::map<long, PathNode*> getNext();

    /**
     * @brief Adds a pointer to a next node in the parallel group-specific topology path.
     * @param id The unique ID associated with the next node.
     * @param next A pointer to the next node to add.
     */
    void addNext(long id, PathNode* next);
};

#endif // SCHEDULING_PARALLELGROUPPATHNODE_H

