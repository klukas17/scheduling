//
// Created by mihael on 29/04/23.
//

#include "MachineNode.h"

MachineNode::MachineNode(long id, MachineType *machine_type) : GenotypeNode(id) {
    this->machine_type = machine_type;
    this->node_type = MACHINE_NODE_TYPE;
}

MachineType *MachineNode::getMachineType() {
    return machine_type;
}