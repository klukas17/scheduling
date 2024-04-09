//
// Created by mihael on 29/04/23.
//

#include "JobType.h"
#include "Machine.h"
#include "MachinePathNode.h"
#include "MachinePathTreeNode.h"
#include "OpenGroup.h"
#include "OpenGroupPathNode.h"
#include "OpenGroupPathTreeNode.h"
#include "ParallelGroup.h"
#include "ParallelGroupPathNode.h"
#include "ParallelGroupPathTreeNode.h"
#include "RouteGroup.h"
#include "RouteGroupPathNode.h"
#include "SchedulingError.h"
#include "SerialGroup.h"
#include "SerialGroupPathNode.h"
#include "ranges"
#include "RouteGroupPathTreeNode.h"
#include "SerialGroupPathTreeNode.h"

JobType::JobType(long const id, bool const preempt) {
    this->id = id;
    this->preempt = preempt;
}

long JobType::getId() const {
    return id;
}

double JobType::getProcessingTime(long const machine_type_id) {
    return processing_times[machine_type_id];
}

void JobType::setProcessingTime(long const machine_type_id, double const processing_time) {
    processing_times[machine_type_id] = processing_time;
}

std::set<long> JobType::getForbiddenMachineTypes() {
    return forbidden_machine_types;
}

void JobType::addForbiddenMachineType(long const machine_type_id) {
    forbidden_machine_types.insert(machine_type_id);
}

bool JobType::getPreempt() const {
    return preempt;
}

std::tuple<PathNode*, PathTreeNode*, std::set<long>> JobType::prepareDataForJobSequenceGenerator(TopologyElement* topology_element) {
    auto [root_path_node, root_path_tree_node] = buildPaths(topology_element);
    return {root_path_node, root_path_tree_node, calculateIntersectionOfPaths(root_path_node)};
}

std::set<long> JobType::calculateIntersectionOfPaths(PathNode* path_node) {

    if (path_node == nullptr) {
        return {};
    }

    auto const topology_element_type = path_node->getTopologyElement()->getTopologyElementType();
    auto const machine_id = path_node->getTopologyElement()->getId();

    switch (topology_element_type) {

    case ABSTRACT_TOPOLOGY_ELEMENT:
        {
            throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in JobType::calculateIntersectionOfPaths function.");
        }

    case MACHINE_TOPOLOGY_ELEMENT:
        {
            auto result = calculateIntersectionOfPaths(dynamic_cast<MachinePathNode*>(path_node)->getNext());
            result.insert(machine_id);
            return result;
        }

    case SERIAL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto result = calculateIntersectionOfPaths(dynamic_cast<SerialGroupPathNode*>(path_node)->getNext());
            result.insert(machine_id);
            return result;
        }

    case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const next_map = dynamic_cast<ParallelGroupPathNode*>(path_node)->getNext();
            std::vector<PathNode*> children;
            children.reserve(next_map.size());
            for (auto child : next_map | std::views::values) {
                children.push_back(child);
            }
            std::set<long> result;
            if (!children.empty()) {
                result = calculateIntersectionOfPaths(children[0]);
                for (int i = 1; i < children.size(); i++) {
                    auto child_result = calculateIntersectionOfPaths(children[1]);
                    std::set<long> next_result;
                    std::set_intersection(result.begin(), result.end(), child_result.begin(), child_result.end(), std::inserter(next_result, next_result.begin()));
                    result = next_result;
                }
            }
            result.insert(machine_id);
            return result;
        }

    case ROUTE_GROUP_TOPOLOGY_ELEMENT:
        {
            auto result = calculateIntersectionOfPaths(dynamic_cast<RouteGroupPathNode*>(path_node)->getNext());
            result.insert(machine_id);
            return result;
        }

    case OPEN_GROUP_TOPOLOGY_ELEMENT:
        {
            auto result = calculateIntersectionOfPaths(dynamic_cast<OpenGroupPathNode*>(path_node)->getNext());
            result.insert(machine_id);
            return result;
        }
    }
}

std::tuple<PathNode*, PathTreeNode*> JobType::buildPaths(TopologyElement* topology_element) {
    auto const topology_element_type = topology_element->getTopologyElementType();
    auto const machine_id = topology_element->getId();

    if (topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        if (auto const machine_type_id = dynamic_cast<Machine*>(topology_element)->getMachineType()->getId(); forbidden_machine_types.contains(machine_type_id)) {
            return {nullptr, nullptr};
        }
    }

    switch (topology_element_type) {

    case ABSTRACT_TOPOLOGY_ELEMENT:
        {
            throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in JobType::buildPaths function.");
        }

    case MACHINE_TOPOLOGY_ELEMENT:
        {
            auto const machine_element = dynamic_cast<Machine*>(topology_element);
            auto const machine_path_node = new MachinePathNode(machine_id, machine_element);
            auto machine_path_tree_node = new MachinePathTreeNode(machine_path_node);
            return {machine_path_node, machine_path_tree_node};
        }

    case SERIAL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const serial_group_element = dynamic_cast<SerialGroup*>(topology_element);
            auto const serial_group_path_node = new SerialGroupPathNode(machine_id, serial_group_element);
            auto const serial_group_path_tree_node = new SerialGroupPathTreeNode(serial_group_path_node);
            std::vector<PathNode*> child_path_nodes;
            std::vector<PathTreeNode*> child_path_tree_nodes;
            for (auto const child_element : serial_group_element->getChildren()) {
                auto [child_path_node, child_path_tree_node] = buildPaths(child_element);
                if (!child_path_node) {
                    for (auto const child : child_path_tree_nodes) {
                        child->deletePathTreeNode();
                    }
                    for (auto const child : child_path_nodes) {
                        child->deletePathNode();
                    }
                    serial_group_path_tree_node->deletePathTreeNode();
                    serial_group_path_node->deletePathNode();
                    return {nullptr, nullptr};
                }
                child_path_nodes.push_back(child_path_node);
                child_path_tree_nodes.push_back(child_path_tree_node);
            }
            if (child_path_nodes.empty()) {
                serial_group_path_tree_node->deletePathTreeNode();
                serial_group_path_node->deletePathNode();
                return {nullptr, nullptr};
            }
            for (int i = 0; i < child_path_nodes.size() - 1; i++) {
                connectGraphsOfPathNodes(child_path_nodes[i], child_path_nodes[i + 1]);
            }
            connectGraphsOfPathNodes(serial_group_path_node, child_path_nodes[0]);
            for (auto const child : child_path_tree_nodes)
            {
                serial_group_path_tree_node->addChild(child);
            }
            return {serial_group_path_node, serial_group_path_tree_node};
        }

    case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const parallel_group_element = dynamic_cast<ParallelGroup*>(topology_element);
            auto const parallel_group_path_node = new ParallelGroupPathNode(machine_id, parallel_group_element);
            auto const parallel_group_path_tree_node = new ParallelGroupPathTreeNode(parallel_group_path_node);
            for (auto const child_element : parallel_group_element->getChildren()) {
                if (auto const [child_path_node, child_path_tree_node] = buildPaths(child_element); child_path_node) {
                    parallel_group_path_node->setNext(child_element->getId(), child_path_node);
                    parallel_group_path_tree_node->addChild(child_path_tree_node);
                }
            }
            if (parallel_group_path_node->getNext().empty()) {
                parallel_group_path_tree_node->deletePathTreeNode();
                parallel_group_path_node->deletePathNode();
                return {nullptr, nullptr};
            }
            return {parallel_group_path_node, parallel_group_path_tree_node};
        }

    case ROUTE_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const route_group_element = dynamic_cast<RouteGroup*>(topology_element);
            auto const route_group_path_node = new RouteGroupPathNode(machine_id, route_group_element);
            auto const route_group_path_tree_node = new RouteGroupPathTreeNode(route_group_path_node);
            for (auto const child_element : route_group_element->getChildren()) {
                if (auto [child_path_node, child_path_tree_node] = buildPaths(child_element); child_path_node) {
                    route_group_path_node->addChild(child_path_node, child_element->getId());
                    route_group_path_tree_node->addChild(child_path_tree_node);
                }
            }
            return {route_group_path_node, route_group_path_tree_node};
        }

    case OPEN_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const open_group_element = dynamic_cast<OpenGroup*>(topology_element);
            auto const open_group_path_node = new OpenGroupPathNode(machine_id, open_group_element);
            auto const open_group_path_tree_node = new OpenGroupPathTreeNode(open_group_path_node);
            for (auto const child_element : open_group_element->getChildren()) {
                if (auto [child_path_node, child_path_tree_node] = buildPaths(child_element); child_path_node) {
                    open_group_path_node->addChild(child_path_node, child_element->getId());
                    open_group_path_tree_node->addChild(child_path_tree_node);
                }
            }
            return {open_group_path_node, open_group_path_tree_node};
        }
    }
}

void JobType::connectGraphsOfPathNodes(PathNode* path_node, PathNode* next_path_node) {

    if (path_node == next_path_node) {
        return;
    }

    switch (path_node->getTopologyElement()->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in JobSequenceParser::connectGraphsOfJobPathNodes function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            {
                if (auto const machine_path_node = dynamic_cast<MachinePathNode*>(path_node); machine_path_node->getNext()) {
                    connectGraphsOfPathNodes(machine_path_node->getNext(), next_path_node);
                }
                else {
                    machine_path_node->setNext(next_path_node);
                }
                break;
            }

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const serial_group_path_node = dynamic_cast<SerialGroupPathNode*>(path_node); serial_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(serial_group_path_node->getNext(), next_path_node);
                }
                else {
                    serial_group_path_node->setNext(next_path_node);
                }
                break;
            }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const parallel_group_path_node = dynamic_cast<ParallelGroupPathNode*>(path_node); !parallel_group_path_node->getNext().empty()) {
                    for (auto [_, child] : parallel_group_path_node->getNext()) {
                        connectGraphsOfPathNodes(child, next_path_node);
                    }
                }
                else {
                    parallel_group_path_node->setNext(next_path_node->getTopologyElement()->getId(), next_path_node);
                }
                break;
            }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const route_group_path_node = dynamic_cast<RouteGroupPathNode*>(path_node); route_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(route_group_path_node->getNext(), next_path_node);
                }
                else {
                    route_group_path_node->setNext(next_path_node);
                }
                break;
            }

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const open_group_path_node = dynamic_cast<OpenGroupPathNode*>(path_node); open_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(open_group_path_node->getNext(), next_path_node);
                }
                else {
                    open_group_path_node->setNext(next_path_node);
                }
                break;
            }
    }
}
