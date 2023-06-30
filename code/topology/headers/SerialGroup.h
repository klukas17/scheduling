//
// Created by mihael on 30/04/23.
//

/**
 * @file SerialGroup.h
 * @brief Defines the SerialGroup class for representing a serial group in a topology.
 */

#ifndef SCHEDULING_SERIALGROUP_H
#define SCHEDULING_SERIALGROUP_H

#include "Group.h"

/**
 * @class SerialGroup
 * @brief Represents a serial group in a topology.
 *
 * The SerialGroup class is a derived class of the Group class and represents a serial group in a topology.
 * It inherits attributes and functionality from the Group class.
 */
class SerialGroup : public Group {
public:
    /**
     * @brief Constructs a SerialGroup object with the given ID.
     * @param id The ID of the serial group.
     */
    explicit SerialGroup(long id);
};

#endif //SCHEDULING_SERIALGROUP_H
