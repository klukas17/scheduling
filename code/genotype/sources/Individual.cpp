//
// Created by mihael on 29/04/23.
//

/**
 * @file Individual.cpp
 * @brief Implements the member functions of the Individual class.
 */

#include "Individual.h"
#include "Machine.h"
#include "MachineNode.h"
#include "SerialGroup.h"
#include "SerialGroupNode.h"
#include "ParallelGroup.h"
#include "ParallelGroupNode.h"
#include "RouteGroup.h"
#include "RouteGroupNode.h"
#include "OpenGroup.h"
#include "OpenGroupNode.h"

Individual::Individual(Topology *topology) {
    this->root_node = createNode(topology->getRootElement());
}

GenotypeNode *Individual::createNode(TopologyElement *topology_element) {

    switch (topology_element->getTopologyElementType()) {

        case MACHINE_TOPOLOGY_ELEMENT: {
            auto machine_element = (Machine*) topology_element;
            auto node = new MachineNode(topology_element->getId(), machine_element->getMachineType());
            for (auto predecessor_id : topology_element->getPredecessorIds()) {
                node->addPredecessorId(predecessor_id);
            }
            return node;
        }

        case SERIAL_GROUP_TOPOLOGY_ELEMENT: {
            auto node = new SerialGroupNode(topology_element->getId());
            for (auto predecessor_id : topology_element->getPredecessorIds()) {
                node->addPredecessorId(predecessor_id);
            }
            for (auto child : ((SerialGroup*)topology_element)->getChildren()) {
                node->addNodeToBody(createNode(child));
            }
            return node;
        }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT: {
            auto node = new ParallelGroupNode(topology_element->getId());
            for (auto predecessor_id : topology_element->getPredecessorIds()) {
                node->addPredecessorId(predecessor_id);
            }
            for (auto child : ((ParallelGroup*)topology_element)->getChildren()) {
                node->addNodeToBody(createNode(child));
            }
            return node;
        }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT: {
            auto node = new RouteGroupNode(topology_element->getId());
            for (auto predecessor_id : topology_element->getPredecessorIds()) {
                node->addPredecessorId(predecessor_id);
            }
            for (auto child : ((RouteGroup*)topology_element)->getChildren()) {
                node->addNodeToBody(createNode(child));
            }
            return node;
        }

        case OPEN_GROUP_TOPOLOGY_ELEMENT: {
            auto node = new OpenGroupNode(topology_element->getId());
            for (auto predecessor_id : topology_element->getPredecessorIds()) {
                node->addPredecessorId(predecessor_id);
            }
            for (auto child : ((OpenGroup*)topology_element)->getChildren()) {
                node->addNodeToBody(createNode(child));
            }
            return node;
        }

        default: {
            // todo:error
            break;
        }
    }
}

GenotypeNode *Individual::getRootNode() {
    return root_node;
}

JobProcessingRoute *Individual::getProcessingRoute(long job_id) {
    return processing_routes[job_id];
}

std::map<long, JobProcessingRoute *> Individual::getProcessingRoutes() {
    return processing_routes;
}

void Individual::setProcessingRoute(long job_id, JobProcessingRoute *job_processing_route) {
    processing_routes[job_id] = job_processing_route;
}