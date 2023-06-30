//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINE_H
#define SCHEDULING_MACHINE_H

/**
 * @file Machine.h
 * @brief Defines the Machine class for representing a machine in a topology.
 */

#include "TopologyElement.h"
#include "MachineType.h"

/**
 * @class Machine
 * @brief Represents a machine in a topology.
 *
 * The Machine class is a derived class of the TopologyElement class and represents a specific machine in a topology.
 * It inherits attributes and functionality from the TopologyElement class and adds a machine type.
 */
class Machine : public TopologyElement {
private:
    MachineType* machine_type; /**< Pointer to the machine type associated with the machine. */

public:
    /**
     * @brief Constructs a Machine object with the given ID and machine type.
     * @param id The ID of the machine.
     * @param machine_type Pointer to the machine type associated with the machine.
     */
    Machine(long id, MachineType* machine_type);

    /**
     * @brief Returns the machine type associated with the machine.
     * @return Pointer to the machine type associated with the machine.
     */
    MachineType* getMachineType();
};

#endif //SCHEDULING_MACHINE_H
