//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineType.h
 * @brief Defines the MachineType class for representing machine types.
 */

#ifndef SCHEDULING_MACHINETYPE_H
#define SCHEDULING_MACHINETYPE_H

#include "SetupRules.h"
#include "JobTypeMap.h"
#include <vector>
#include <tuple>

/**
 * @class MachineType
 * @brief Represents a machine type.
 *
 * The MachineType class represents a type of machine that can be used for job processing.
 * It includes information about the machine type's ID, preemption policy, and setup rules.
 */
class MachineType {
protected:
    long id; /**< The ID of the machine type */
    bool preempt; /**< Indicates whether preemption is allowed for this machine type */
    SetupRules* setup_rules; /**< Pointer to the setup rules for this machine type. */
    std::vector<std::tuple<long, long, long>> setup_rules_raw_data; /**< Raw data for setup rules. */

public:
    /**
     * @brief Constructs a MachineType object with the given ID and setup rule data.
     * @param id The ID of the machine type.
     * @param preempt Indicates whether preemption is allowed for this machine type.
     * @param setup_rules_raw_data A vector containing raw setup rule data.
     */
    MachineType(long id, bool preempt, std::vector<std::tuple<long, long, long>> setup_rules_raw_data);

    /**
     * @brief Gets the ID of the machine type.
     * @return The ID of the machine type.
     */
    [[nodiscard]] long getId() const;

    /**
     * @brief Checks if preemption is allowed for this machine type.
     * @return true if preemption is allowed, false otherwise.
     */
    [[nodiscard]] bool getPreempt() const;

    /**
     * @brief Retrieves the setup rules for this machine type.
     * @return A pointer to the SetupRules object representing the setup rules.
     */
    SetupRules* getSetupRules();

    /**
     * @brief Constructs the setup rules for this machine type using job type mapping.
     * @param job_type_map A pointer to the JobTypeMap object for mapping job types.
     */
    void constructSetupRules(JobTypeMap* job_type_map);
};

#endif //SCHEDULING_MACHINETYPE_H
