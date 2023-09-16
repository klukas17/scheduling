//
// Created by mihael on 29/06/23.
//

/**
 * @file PathNode.cpp
 * @brief Implements the member functions of the PathNode class.
 */

#include "PathNode.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "OpenGroupPathNode.h"

PathNode::PathNode(long path_node_id, TopologyElement* topology_element) {
    this->path_node_id = path_node_id;
    this->topology_element = topology_element;
}

PathNode::~PathNode() = default;

long PathNode::getPathNodeId() {
    return path_node_id;
}

TopologyElement *PathNode::getTopologyElement() {
    return topology_element;
}

std::vector<Prerequisite *> PathNode::getPrerequisites() {
    return prerequisites;
}

void PathNode::addPrerequisite(Prerequisite *prerequisite) {
    prerequisites.push_back(prerequisite);
}

void PathNode::deletePathNode() {

    auto topology_element_type = topology_element->getTopologyElementType();
    std::set<PathNode*> elements;

    if (topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Trying to delete an abstract topology element.");
    }

    else if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_path_node = (MachinePathNode*) this;
        findSubPathNodes(machine_path_node->getNext(), elements);
    }

    else if (topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto serial_group_path_node = (SerialGroupPathNode*) this;
        findSubPathNodes(serial_group_path_node->getNext(), elements);
    }

    else if (topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_path_node = (ParallelGroupPathNode*) this;
        for (auto next : parallel_group_path_node->getNext()) {
            findSubPathNodes(next.second, elements);
        }
    }

    else if (topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto route_group_path_node = (RouteGroupPathNode*) this;
        findSubPathNodes(route_group_path_node->getNext(), elements);
    }

    else if (topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto open_group_path_node = (OpenGroupPathNode*) this;
        for (auto sub_path_node : open_group_path_node->getSubPathNodes()) {
            findSubPathNodes(sub_path_node.second, elements);
        }
        findSubPathNodes(open_group_path_node->getNext(), elements);
    }

    elements.insert(this);

    std::vector<PathNode*> nodes_to_be_deleted;
    for (auto node : elements) {
        nodes_to_be_deleted.push_back(node);
    }

    for (auto & node : nodes_to_be_deleted) {
        delete node;
    }
}

void PathNode::findSubPathNodes(PathNode *current_node, std::set<PathNode *> &sub_path_nodes) {

    if (!current_node) {
        return;
    }

    auto topology_element_type = current_node->getTopologyElement()->getTopologyElementType();

    if (topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Trying to delete an abstract topology element.");
    }

    else if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine_path_node = (MachinePathNode*) current_node;
        findSubPathNodes(machine_path_node->getNext(), sub_path_nodes);
    }

    else if (topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        auto serial_group_path_node = (SerialGroupPathNode*) current_node;
        findSubPathNodes(serial_group_path_node->getNext(), sub_path_nodes);
    }

    else if (topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_path_node = (ParallelGroupPathNode*) current_node;
        for (auto next : parallel_group_path_node->getNext()) {
            findSubPathNodes(next.second, sub_path_nodes);
        }
    }

    else if (topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        auto route_group_path_node = (RouteGroupPathNode*) current_node;
        findSubPathNodes(route_group_path_node->getNext(), sub_path_nodes);
    }

    else if (topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        auto open_group_path_node = (OpenGroupPathNode*) current_node;
        for (auto sub_path_node : open_group_path_node->getSubPathNodes()) {
            findSubPathNodes(sub_path_node.second, sub_path_nodes);
        }
        findSubPathNodes(open_group_path_node->getNext(), sub_path_nodes);
    }

    sub_path_nodes.insert(current_node);
}