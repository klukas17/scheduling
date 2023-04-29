//
// Created by mihael on 29/04/23.
//

#include "Machine.h"

Machine::Machine(long id, MachineType *machineType) {
    this->id = id;
    this->machineType = machineType;
    this->topologyElementType = MACHINE;
}