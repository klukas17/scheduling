//
// Created by mihael on 01/05/23.
//

/**
 * @file ParallelGroupNode.h
 * @brief Defines the ParallelGroupNode class for representing a parallel group node within an individual's genotype.
 */

#ifndef SCHEDULING_PARALLELGROUPNODE_H
#define SCHEDULING_PARALLELGROUPNODE_H

#include "GroupNode.h"

/**
 * @class ParallelGroupNode
 * @brief Represents a parallel group node within an individual's genotype.
 *
 * The ParallelGroupNode class is derived from the GroupNode class and represents a node in an individual's genotype that
 * signifies a parallel group of nodes. It inherits attributes for a group of nodes and represents nodes that can be
 * executed in parallel.
 */
class ParallelGroupNode : public GroupNode {
public:
    /**
     * @brief Constructs a ParallelGroupNode object with the provided identifier.
     * @param id The identifier for the parallel group node.
     */
    explicit ParallelGroupNode(long id);
};

#endif //SCHEDULING_PARALLELGROUPNODE_H
