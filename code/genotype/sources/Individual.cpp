//
// Created by mihael on 29/04/23.
//

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
            return new MachineNode(topology_element->getId(), machine_element->getMachineType());
        }

        case SERIAL_GROUP_TOPOLOGY_ELEMENT: {
            auto node = new SerialGroupNode(topology_element->getId());
            for (auto body_element : ((SerialGroup*)topology_element)->getBody()) {
                node->addNodeToBody(createNode(body_element));
            }
            return node;
        }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT: {
            auto node = new ParallelGroupNode(topology_element->getId());
            for (auto body_element : ((ParallelGroup*)topology_element)->getBody()) {
                node->addNodeToBody(createNode(body_element));
            }
            return node;
        }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT: {
            auto node = new RouteGroupNode(topology_element->getId());
            for (auto body_element : ((RouteGroup*)topology_element)->getBody()) {
                node->addNodeToBody(createNode(body_element));
            }
            return node;
        }

        case OPEN_GROUP_TOPOLOGY_ELEMENT: {
            auto node = new OpenGroupNode(topology_element->getId());
            for (auto body_element : ((OpenGroup*)topology_element)->getBody()) {
                node->addNodeToBody(createNode(body_element));
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