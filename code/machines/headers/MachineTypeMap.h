//
// Created by mihael on 30/06/23.
//

/**
 * @file MachineTypeMap.h
 * @brief Defines the MachineTypeMap class for representing a map of all machine types.
 */

#ifndef SCHEDULING_MACHINETYPEMAP_H
#define SCHEDULING_MACHINETYPEMAP_H

#include <map>
#include "MachineType.h"
#include "JobTypeMap.h"

/**
 * @class MachineTypeMap
 * @brief Represents a map of all machine types.
 *
 * The MachineTypeMap class provides functionality for managing a map of machine types, where each
 * machine type is associated with a unique ID.
 */
class MachineTypeMap {
private:
    std::map<long, MachineType*> machine_type_map; /**< The map of machine types with their IDs as keys */

public:
    /**
     * @brief Constructs an empty MachineTypeMap object.
     */
    MachineTypeMap();

    /**
     * @brief Gets the map of machine types.
     * @return The map of machine types with their IDs as keys.
     */
    std::map<long, MachineType*> getMachineTypeMap();

    /**
     * @brief Gets the machine type with the specified ID.
     * @param machine_type_id The ID of the machine type to retrieve.
     * @return A pointer to the MachineType object, or nullptr if not found.
     */
    MachineType* getMachineType(long machine_type_id);

    /**
     * @brief Adds a machine type to the map.
     * @param machine_type_id The ID of the machine type to add.
     * @param machine_type A pointer to the MachineType object to add.
     * @throws SchedulingError if an entry with the key machine_type_id is already present in the map.
     */
    void addMachineType(long machine_type_id, MachineType* machine_type);

    /**
     * @brief Constructs the setup rules for machine types using job type mapping.
     * @param job_type_map A pointer to the JobTypeMap object for mapping job types.
     */
    void constructSetupRules(JobTypeMap* job_type_map);
};

#endif // SCHEDULING_MACHINETYPEMAP_H
