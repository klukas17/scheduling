//
// Created by mihael on 01/05/23.
//

#include "Group.h"

Group::Group(long id) : TopologyElement(id) {
    this->general_topology_element_type = GROUP_GENERAL_TOPOLOGY_ELEMENT;
}

Group::~Group() = default;

std::vector<TopologyElement *> Group::getBody() {
    return body;
}

void Group::addElementToBody(TopologyElement *element) {
    body.push_back(element);
}