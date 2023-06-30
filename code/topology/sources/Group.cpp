//
// Created by mihael on 01/05/23.
//

/**
 * @file Group.cpp
 * @brief Implements the member functions of the Group class.
 */

#include "Group.h"

Group::Group(long id) : TopologyElement(id) {
    this->general_topology_element_type = GROUP_GENERAL_TOPOLOGY_ELEMENT;
}

Group::~Group() = default;

std::vector<TopologyElement*> Group::getChildren() {
    return children;
}

void Group::addChild(TopologyElement* child) {
    children.push_back(child);
}
