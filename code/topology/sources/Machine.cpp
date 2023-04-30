//
// Created by mihael on 29/04/23.
//

#include "Machine.h"

Machine::Machine(long id, MachineType *machine_type) {
    this->id = id;
    this->machine_type = machine_type;
    this->topology_element_type = MACHINE_TOPOLOGY_ELEMENT;
}

long Machine::getId() const {
    return id;
}

MachineType *Machine::getMachineType() {
    return machine_type;
}