//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineNode.cpp
 * @brief Implements the member functions of the MachineNode class.
 */

#include "MachineNode.h"

MachineNode::MachineNode(long id, MachineType *machine_type) : GenotypeNode(id) {
    this->machine_type = machine_type;
    this->node_type = MACHINE_NODE;
    this->general_node_type = MACHINE_GENERAL_NODE;
}

MachineType *MachineNode::getMachineType() {
    return machine_type;
}