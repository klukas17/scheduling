//
// Created by mihael on 29/04/23.
//

#include "Individual.h"
#include "Machine.h"
#include "MachineNode.h"

Individual::Individual(Topology *topology) {

    TopologyElement* topology_root_element = topology->getRootElement();
    TopologyElementType topology_root_element_type = topology_root_element->getTopologyElementType();

    if (topology_root_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        auto machine = (Machine*) topology_root_element;
        GenotypeNode* genotype_node = new MachineNode(machine->getId());
        this->root_node = genotype_node;
    }
}

GenotypeNode *Individual::getRootNode() {
    return root_node;
}