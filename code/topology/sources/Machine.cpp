//
// Created by mihael on 29/04/23.
//

#include "Machine.h"

Machine::Machine(long const id, MachineType *machine_type) : TopologyElement(id) {
    this->machine_type = machine_type;
    this->topology_element_type = MACHINE_TOPOLOGY_ELEMENT;
    this->general_topology_element_type = MACHINE_GENERAL_TOPOLOGY_ELEMENT;
}

MachineType *Machine::getMachineType() const {
    return machine_type;
}
