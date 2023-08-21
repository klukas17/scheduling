//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineNode.h
 * @brief Defines the MachineNode class for representing a machine node within an individual's genotype.
 */

#ifndef SCHEDULING_MACHINENODE_H
#define SCHEDULING_MACHINENODE_H

#include "GenotypeNode.h"
#include "MachineType.h"
#include "vector"

/**
 * @class MachineNode
 * @brief Represents a machine node within an individual's genotype.
 *
 * The MachineNode class is derived from the GenotypeNode class and represents a node in an individual's genotype that
 * corresponds to a machine. It includes attributes to store the associated machine type.
 */
class MachineNode : public GenotypeNode {
private:
    MachineType* machine_type; /**< Pointer to the associated machine type. */
public:
    /**
     * @brief Constructs a MachineNode object with the provided identifier and machine type.
     * @param id The identifier for the machine node.
     * @param machine_type A pointer to the associated machine type.
     */
    MachineNode(long id, MachineType* machine_type);

    /**
     * @brief Retrieves the associated machine type.
     * @return A pointer to the associated MachineType object.
     */
    MachineType* getMachineType();
};

#endif //SCHEDULING_MACHINENODE_H

