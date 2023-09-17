//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineType.cpp
 * @brief Implements the member functions of the MachineType class.
 */

#include "MachineType.h"

MachineType::MachineType(long id, bool preempt) {
    this->id = id;
    this->preempt = preempt;
}

long MachineType::getId() const {
    return id;
}

bool MachineType::getPreempt() const {
    return preempt;
}