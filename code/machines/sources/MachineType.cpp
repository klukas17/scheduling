//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineType.cpp
 * @brief Implements the member functions of the MachineType class.
 */

#include "MachineType.h"

MachineType::MachineType(long id) {
    this->id = id;
}

long MachineType::getId() const {
    return id;
}