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

        default: {
            // todo:error
            break;
        }
    }
}

GenotypeNode *Individual::getRootNode() {
    return root_node;
}