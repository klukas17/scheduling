//
// Created by mihael on 01/05/23.
//

#include "OpenGroup.h"

OpenGroup::OpenGroup(long const id) : Group(id) {
    this->topology_element_type = OPEN_GROUP_TOPOLOGY_ELEMENT;
}
