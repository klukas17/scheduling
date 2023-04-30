//
// Created by mihael on 30/04/23.
//

#include "SerialGroup.h"

SerialGroup::SerialGroup(long id) : TopologyElement(id) {
    this->topology_element_type = SERIAL_GROUP_TOPOLOGY_ELEMENT;
}

std::vector<TopologyElement *> SerialGroup::getBody() {
    return body;
}

void SerialGroup::addElementToBody(TopologyElement *element) {
    body.push_back(element);
}