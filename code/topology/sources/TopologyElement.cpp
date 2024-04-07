//
// Created by mihael on 29/04/23.
//


#include "TopologyElement.h"

TopologyElement::TopologyElement(long const id) {
    this->id = id;
    this->topology_element_type = ABSTRACT_TOPOLOGY_ELEMENT;
    this->general_topology_element_type = ABSTRACT_GENERAL_TOPOLOGY_ELEMENT;
    this->buffer_size = 0;
}

TopologyElement::~TopologyElement() = default;

long TopologyElement::getId() const {
    return id;
}

TopologyElementType TopologyElement::getTopologyElementType() const {
    return topology_element_type;
}

GeneralTopologyElementType TopologyElement::getGeneralTopologyElementType() const {
    return general_topology_element_type;
}

std::set<long> TopologyElement::getPredecessorIds() {
    return predecessor_element_ids;
}

void TopologyElement::addPredecessorId(long const element_id) {
    predecessor_element_ids.insert(element_id);
}

std::vector<Breakdown *> TopologyElement::getBreakdowns() {
    return breakdowns;
}

void TopologyElement::addBreakdown(Breakdown *breakdown) {
    breakdowns.push_back(breakdown);
}

long TopologyElement::getBufferSize() const {
    return buffer_size;
}

void TopologyElement::setBufferSize(long const buffer_size) {
    this->buffer_size = buffer_size;
}