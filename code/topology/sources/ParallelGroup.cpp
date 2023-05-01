//
// Created by mihael on 01/05/23.
//

#include "ParallelGroup.h"

ParallelGroup::ParallelGroup(long id) : TopologyElement(id) {
    this->topology_element_type = PARALLEL_GROUP_TOPOLOGY_ELEMENT;
}

std::vector<TopologyElement *> ParallelGroup::getBody() {
    return body;
}

void ParallelGroup::addElementToBody(TopologyElement *element) {
    body.push_back(element);
}