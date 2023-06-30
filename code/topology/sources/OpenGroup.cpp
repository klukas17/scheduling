//
// Created by mihael on 01/05/23.
//

/**
 * @file OpenGroup.cpp
 * @brief Implements the member functions of the OpenGroup class.
 */

#include "OpenGroup.h"

OpenGroup::OpenGroup(long id) : Group(id) {
    this->topology_element_type = OPEN_GROUP_TOPOLOGY_ELEMENT;
}
