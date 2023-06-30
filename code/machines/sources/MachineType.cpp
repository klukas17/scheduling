//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineType.cpp
 * @brief Implements the member functions of the MachineType class
 */

#include "MachineType.h"

/**
 * @brief Constructs a MachineType object
 * @param id The ID of the machine type
 */
MachineType::MachineType(long id) {
    this->id = id;
}

/**
 * @brief Gets the ID of the machine type
 * @return The ID of the machine type
 */
long MachineType::getId() const {
    return id;
}