//
// Created by mihael on 01/05/23.
//

#include "ParallelGroup.h"

ParallelGroup::ParallelGroup(long id) : Group(id) {
    this->topology_element_type = PARALLEL_GROUP_TOPOLOGY_ELEMENT;
}