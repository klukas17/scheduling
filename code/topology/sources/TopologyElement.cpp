//
// Created by mihael on 29/04/23.
//

#include "TopologyElement.h"

TopologyElement::TopologyElement() {
    this->topology_element_type = ABSTRACT_TOPOLOGY_ELEMENT;
}

TopologyElement::~TopologyElement() = default;

TopologyElementType TopologyElement::getTopologyElementType() {
    return topology_element_type;
}