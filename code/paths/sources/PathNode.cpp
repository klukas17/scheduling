//
// Created by mihael on 29/06/23.
//

#include "PathNode.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "OpenGroupPathNode.h"

PathNode::PathNode(long const path_node_id, TopologyElement* topology_element) {
    this->path_node_id = path_node_id;
    this->topology_element = topology_element;
}

PathNode::~PathNode() = default;

long PathNode::getPathNodeId() const {
    return path_node_id;
}

TopologyElement *PathNode::getTopologyElement() const {
    return topology_element;
}

std::vector<Prerequisite *> PathNode::getPrerequisites() {
    return prerequisites;
}

void PathNode::addPrerequisite(Prerequisite *prerequisite) {
    prerequisites.push_back(prerequisite);
}

void PathNode::deletePathNode() {

    auto const topology_element_type = topology_element->getTopologyElementType();
    std::set<PathNode*> elements;

    if (topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Trying to delete an abstract topology element.");
    }

    if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto const machine_path_node = dynamic_cast<MachinePathNode*>(this);
        findSubPathNodes(machine_path_node->getNext(), elements);
    }

    else if (topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto const serial_group_path_node = dynamic_cast<SerialGroupPathNode*>(this);
        findSubPathNodes(serial_group_path_node->getNext(), elements);
    }

    else if (topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        for (auto [_, next] : dynamic_cast<ParallelGroupPathNode*>(this)->getNext()) {
            findSubPathNodes(next, elements);
        }
    }

    else if (topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto const route_group_path_node = dynamic_cast<RouteGroupPathNode*>(this);
        findSubPathNodes(route_group_path_node->getNext(), elements);
    }

    else if (topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto const open_group_path_node = dynamic_cast<OpenGroupPathNode*>(this);
        for (auto const [_, sub_path_node] : open_group_path_node->getSubPathNodes()) {
            findSubPathNodes(sub_path_node, elements);
        }
        findSubPathNodes(open_group_path_node->getNext(), elements);
    }

    elements.insert(this);

    std::vector<PathNode*> nodes_to_be_deleted;
    nodes_to_be_deleted.reserve(elements.size());
    for (auto node : elements) {
        nodes_to_be_deleted.push_back(node);
    }

    for (auto const & node : nodes_to_be_deleted) {
        delete node;
    }
}

void PathNode::findSubPathNodes(PathNode *current_node, std::set<PathNode *> &sub_path_nodes) {

    if (!current_node) {
        return;
    }

    auto const topology_element_type = current_node->getTopologyElement()->getTopologyElementType();

    if (topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Trying to delete an abstract topology element.");
    }

    if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto const machine_path_node = dynamic_cast<MachinePathNode*>(current_node);
        findSubPathNodes(machine_path_node->getNext(), sub_path_nodes);
    }

    else if (topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto const serial_group_path_node = dynamic_cast<SerialGroupPathNode*>(current_node);
        findSubPathNodes(serial_group_path_node->getNext(), sub_path_nodes);
    }

    else if (topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        for (auto const [_, next] : dynamic_cast<ParallelGroupPathNode*>(current_node)->getNext()) {
            findSubPathNodes(next, sub_path_nodes);
        }
    }

    else if (topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto const route_group_path_node = dynamic_cast<RouteGroupPathNode*>(current_node);
        findSubPathNodes(route_group_path_node->getNext(), sub_path_nodes);
    }

    else if (topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto const open_group_path_node = dynamic_cast<OpenGroupPathNode*>(current_node);
        for (auto const [_, sub_path_node] : open_group_path_node->getSubPathNodes()) {
            findSubPathNodes(sub_path_node, sub_path_nodes);
        }
        findSubPathNodes(open_group_path_node->getNext(), sub_path_nodes);
    }

    sub_path_nodes.insert(current_node);
}