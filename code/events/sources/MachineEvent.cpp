//
// Created by mihael on 30/04/23.
//

/**
 * @file MachineEvent.cpp
 * @brief Implements the member functions of the MachineEvent class.
 */

#include "MachineEvent.h"

MachineEvent::MachineEvent(long time, long machine_id) : Event(time) {
    this->machine_id = machine_id;
}

MachineEvent::~MachineEvent() = default;

long MachineEvent::getMachineId() const {
    return machine_id;
}