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

public:
    /**
     * @brief Constructs a MachineType object.
     * @param id The ID of the machine type.
     */
    explicit MachineType(long id);

    /**
     * @brief Gets the ID of the machine type.
     * @return The ID of the machine type.
     */
    [[nodiscard]] long getId() const;
};

#endif //SCHEDULING_MACHINETYPE_H
