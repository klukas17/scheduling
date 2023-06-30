//
// Created by mihael on 01/05/23.
//

/**
 * @file ParallelGroup.cpp
 * @brief Implements the member functions of the ParallelGroup class.
 */

#include "ParallelGroup.h"

ParallelGroup::ParallelGroup(long id) : Group(id) {
    this->topology_element_type = PARALLEL_GROUP_TOPOLOGY_ELEMENT;
}
