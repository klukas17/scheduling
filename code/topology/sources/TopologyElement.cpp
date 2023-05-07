//
// Created by mihael on 29/04/23.
//

#include "TopologyElement.h"

TopologyElement::TopologyElement(long id) {
    this->id = id;
    this->topology_element_type = ABSTRACT_TOPOLOGY_ELEMENT;
    this->general_topology_element_type = ABSTRACT_GENERAL_TOPOLOGY_ELEMENT;
}

TopologyElement::~TopologyElement() = default;

long TopologyElement::getId() const {
    return id;
}

TopologyElementType TopologyElement::getTopologyElementType() {
    return topology_element_type;
}

GeneralTopologyElementType TopologyElement::getGeneralTopologyElementType() {
    return general_topology_element_type;
}

std::set<long> TopologyElement::getPredecessorIds() {
    return predecessor_element_ids;
}

void TopologyElement::addPredecessorId(long element_id) {
    predecessor_element_ids.insert(element_id);
}