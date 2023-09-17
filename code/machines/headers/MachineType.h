//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineType.h
 * @brief Defines the MachineType class for representing machine types.
 */

#ifndef SCHEDULING_MACHINETYPE_H
#define SCHEDULING_MACHINETYPE_H

/**
 * @class MachineType
 * @brief Class for representing a machine type.
 */
class MachineType {
protected:
    long id; /**< The ID of the machine type */
    bool preempt; /**< Indicates whether preemption is allowed for this machine type */

public:
    /**
     * @brief Constructs a MachineType object.
     * @param id The ID of the machine type.
     */
    MachineType(long id, bool preempt);

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
};

#endif //SCHEDULING_MACHINETYPE_H
