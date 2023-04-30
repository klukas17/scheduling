//
// Created by mihael on 29/04/23.
//

#include "TopologyElement.h"

TopologyElement::TopologyElement(long id) {
    this->id = id;
    this->topology_element_type = ABSTRACT_TOPOLOGY_ELEMENT;
}

TopologyElement::~TopologyElement() = default;

long TopologyElement::getId() const {
    return id;
}

TopologyElementType TopologyElement::getTopologyElementType() {
    return topology_element_type;
}