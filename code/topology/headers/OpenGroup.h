//
// Created by mihael on 01/05/23.
//

/**
 * @file OpenGroup.h
 * @brief Defines the OpenGroup class for representing an open group in a topology.
 */

#ifndef SCHEDULING_OPENGROUP_H
#define SCHEDULING_OPENGROUP_H

#include "Group.h"

/**
 * @class OpenGroup
 * @brief Represents an open group in a topology.
 *
 * The OpenGroup class is a derived class of the Group class and represents an open group in a topology.
 * It inherits attributes and functionality from the Group class.
 */
class OpenGroup : public Group {
public:
    /**
     * @brief Constructs an OpenGroup object with the given ID.
     * @param id The ID of the open group.
     */
    explicit OpenGroup(long id);
};

#endif //SCHEDULING_OPENGROUP_H
