//
// Created by mihael on 01/05/23.
//

/**
 * @file Group.h
 * @brief Defines the Group class for representing a group in a topology.
 */

#ifndef SCHEDULING_GROUP_H
#define SCHEDULING_GROUP_H

#include "TopologyElement.h"
#include <vector>

/**
 * @class Group
 * @brief Represents a group in a topology.
 *
 * The Group class is a derived class of the TopologyElement class and represents a group of elements in a topology.
 * It inherits attributes and functionality from the TopologyElement class and adds the ability to manage child elements.
 */
class Group : public TopologyElement {
protected:
    std::vector<TopologyElement*> children; /**< Vector of pointers to the child elements of the group. */

public:
    /**
     * @brief Constructs a Group object with the given ID.
     * @param id The ID of the group.
     */
    explicit Group(long id);

    /**
     * @brief Pure virtual destructor for the Group class.
     *
     * This makes Group an abstract class, and it cannot be instantiated directly.
     */
    ~Group() override = 0;

    /**
     * @brief Returns a vector of pointers to the child elements of the group.
     * @return A vector of pointers to the child elements of the group.
     */
    std::vector<TopologyElement*> getChildren();

    /**
     * @brief Adds a child element to the group.
     * @param child Pointer to the child element to add.
     */
    void addChild(TopologyElement* child);
};

#endif //SCHEDULING_GROUP_H
