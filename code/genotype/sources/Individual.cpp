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
#include "SchedulingError.h"

Individual::Individual(const Topology *topology) {
    this->root_node = createNode(topology->getRootElement());
    mapGenotypeNodes(this->root_node);
}

GenotypeNode *Individual::createNode(TopologyElement *topology_element) {

    switch (topology_element->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in function Individual::createNode.");

        case MACHINE_TOPOLOGY_ELEMENT: {
            auto const machine_element = dynamic_cast<Machine*>(topology_element);
            auto const node = new MachineNode(topology_element->getId(), machine_element->getMachineType());
            return node;
        }

        case SERIAL_GROUP_TOPOLOGY_ELEMENT: {
            auto const node = new SerialGroupNode(topology_element->getId());
            for (auto const child : dynamic_cast<SerialGroup*>(topology_element)->getChildren()) {
                node->addNodeToBody(createNode(child));
            }
            return node;
        }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT: {
            auto const node = new ParallelGroupNode(topology_element->getId());
            for (auto const child : dynamic_cast<ParallelGroup*>(topology_element)->getChildren()) {
                node->addNodeToBody(createNode(child));
            }
            return node;
        }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT: {
            auto const node = new RouteGroupNode(topology_element->getId());
            for (auto const child : dynamic_cast<RouteGroup*>(topology_element)->getChildren()) {
                node->addNodeToBody(createNode(child));
            }
            return node;
        }

        case OPEN_GROUP_TOPOLOGY_ELEMENT: {
            auto const node = new OpenGroupNode(topology_element->getId());
            for (auto const child : dynamic_cast<OpenGroup*>(topology_element)->getChildren()) {
                node->addNodeToBody(createNode(child));
            }
            return node;
        }
    }
}

GenotypeNode *Individual::getRootNode() const {
    return root_node;
}

std::map<long, GenotypeNode *> Individual::getGenotypeNodeMap() {
    return genotype_node_map;
}

void Individual::mapGenotypeNodes(GenotypeNode *node) {

    switch(node->getGeneralNodeType()) {

        case ABSTRACT_GENERAL_NODE:
            throw SchedulingError("Abstract topology element encountered in function Individual::mapGenotypeNodes.");

        case MACHINE_GENERAL_NODE:
            genotype_node_map[node->getId()] = node;
            break;

        case GROUP_GENERAL_NODE:
            genotype_node_map[node->getId()] = node;
            for (auto const sub_node : dynamic_cast<GroupNode*>(node)->getBody()) {
                mapGenotypeNodes(sub_node);
            }
            break;
    }
}

JobProcessingRoute *Individual::getProcessingRoute(long const job_id) {
    return processing_routes[job_id];
}

std::map<long, JobProcessingRoute *> Individual::getProcessingRoutes() {
    return processing_routes;
}

void Individual::setProcessingRoute(long const job_id, JobProcessingRoute *job_processing_route) {
    processing_routes[job_id] = job_processing_route;
}