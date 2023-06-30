//
// Created by mihael on 30/04/23.
//

/**
 * @file SerialGroup.cpp
 * @brief Implements the member functions of the SerialGroup class.
 */

#include "SerialGroup.h"

SerialGroup::SerialGroup(long id) : Group(id) {
    this->topology_element_type = SERIAL_GROUP_TOPOLOGY_ELEMENT;
}
