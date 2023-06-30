//
// Created by mihael on 01/05/23.
//

/**
 * @file ParallelGroup.h
 * @brief Defines the ParallelGroup class for representing a parallel group in a topology.
 */

#ifndef SCHEDULING_PARALLELGROUP_H
#define SCHEDULING_PARALLELGROUP_H

#include "Group.h"

/**
 * @class ParallelGroup
 * @brief Represents a parallel group in a topology.
 *
 * The ParallelGroup class is a derived class of the Group class and represents a parallel group in a topology.
 * It inherits attributes and functionality from the Group class.
 */
class ParallelGroup : public Group {
public:
    /**
     * @brief Constructs a ParallelGroup object with the given ID.
     * @param id The ID of the parallel group.
     */
    explicit ParallelGroup(long id);
};

#endif //SCHEDULING_PARALLELGROUP_H
