//
// Created by mihael on 29/04/23.
//

/**
 * @file Topology.cpp
 * @brief Implements the member functions of the Topology class.
 */

#include "Topology.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "OpenGroupPathNode.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "OpenGroup.h"

Topology::Topology(TopologyElement* topology_root_element) {
    this->topology_root_element = topology_root_element;
    indexTopologyElementsAndPathNodes(topology_root_element);
    this->root_path_node = path_nodes_map[topology_root_element->getId()];
    buildPaths(topology_root_element, root_path_node, nullptr);
}

TopologyElement* Topology::getRootElement() {
    return topology_root_element;
}

PathNode *Topology::getRootPathNode() {
    return root_path_node;
}

std::map<long, TopologyElement *> Topology::getTopologyElementsMap() {
    return topology_elements_map;
}

std::map<long, PathNode *> Topology::getPathNodesMap() {
    return path_nodes_map;
}

void Topology::indexTopologyElementsAndPathNodes(TopologyElement* node) {

    switch (node->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in Topology::indexPathNodes function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            path_nodes_map[node->getId()] = new MachinePathNode(node);
            break;

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            path_nodes_map[node->getId()] = new SerialGroupPathNode(node);
            for (auto child : ((SerialGroup*)node)->getChildren()) {
                indexTopologyElementsAndPathNodes(child);
            }
            break;

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            path_nodes_map[node->getId()] = new ParallelGroupPathNode(node);
            for (auto child : ((ParallelGroup*)node)->getChildren()) {
                indexTopologyElementsAndPathNodes(child);
            }
            break;

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            path_nodes_map[node->getId()] = new RouteGroupPathNode(node);
            for (auto child : ((RouteGroup*)node)->getChildren()) {
                indexTopologyElementsAndPathNodes(child);
            }
            break;

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            path_nodes_map[node->getId()] = new OpenGroupPathNode(node);
            for (auto child : ((OpenGroup*)node)->getChildren()) {
                indexTopologyElementsAndPathNodes(child);
            }
            break;
    }
}

void Topology::buildPaths(TopologyElement* topology_element, PathNode* node, PathNode* next) {

    auto topology_element_type = node->getTopologyElement()->getTopologyElementType();

    if (topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element encountered in Topology::buildPaths function.");
    }

    else if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        ((MachinePathNode*)node)->setNext(next);
    }

    else if (topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        std::vector<TopologyElement*> topology_elements_children = ((SerialGroup*)topology_element)->getChildren();
        if (topology_elements_children.empty()) return;
        std::vector<PathNode*> path_nodes_children;
        for (auto element : topology_elements_children) {
            path_nodes_children.push_back(path_nodes_map[element->getId()]);
            ((SerialGroupPathNode*)node)->addChild(path_nodes_map[element->getId()]);
        }
        ((SerialGroupPathNode*)node)->setNext(path_nodes_children[0]);
        for (int i = 0; i < path_nodes_children.size(); i++) {
            buildPaths(topology_elements_children[i], path_nodes_children[i],
                       (i < path_nodes_children.size() - 1) ? path_nodes_children[i + 1] : next);
        }

    }

    else if (topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        std::vector<TopologyElement*> topology_elements_children = ((SerialGroup*)topology_element)->getChildren();
        if (topology_elements_children.empty()) return;
        std::vector<PathNode*> path_nodes_children;
        for (auto element : topology_elements_children) {
            path_nodes_children.push_back(path_nodes_map[element->getId()]);
        }
        for (auto child : path_nodes_children) {
            ((ParallelGroupPathNode*)node)->addNext(child->getTopologyElement()->getId(), child);
        }
        for (int i = 0; i < path_nodes_children.size(); i++) {
            buildPaths(topology_elements_children[i], path_nodes_children[i], next);
        }
    }

    else if (topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        std::vector<TopologyElement*> topology_elements_children = ((RouteGroup*)topology_element)->getChildren();
        if (topology_elements_children.empty()) return;
        std::vector<PathNode*> path_nodes_children;
        for (auto element : topology_elements_children) {
            path_nodes_children.push_back(path_nodes_map[element->getId()]);
        }
        ((RouteGroupPathNode*)node)->setNext(next);
        for (int i = 0; i < path_nodes_children.size(); i++) {
            ((RouteGroupPathNode*)node)->addSubPathNode(path_nodes_children[i]);
            buildPaths(topology_elements_children[i], path_nodes_children[i], nullptr);
        }
    }

    else if (topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        std::vector<TopologyElement*> topology_elements_children = ((OpenGroup*)topology_element)->getChildren();
        if (topology_elements_children.empty()) return;
        std::vector<PathNode*> path_nodes_children;
        for (auto element : topology_elements_children) {
            path_nodes_children.push_back(path_nodes_map[element->getId()]);
        }
        ((OpenGroupPathNode*)node)->setNext(next);
        for (int i = 0; i < path_nodes_children.size(); i++) {
            ((OpenGroupPathNode*)node)->addSubPathNode(path_nodes_children[i]);
            buildPaths(topology_elements_children[i], path_nodes_children[i], nullptr);
        }
    }
}