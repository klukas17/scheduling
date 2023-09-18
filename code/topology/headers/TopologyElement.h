//
// Created by mihael on 29/04/23.
//

/**
 * @file TopologyElement.h
 * @brief Defines the TopologyElement class for representing a generic element in a topology.
 */

#ifndef SCHEDULING_TOPOLOGYELEMENT_H
#define SCHEDULING_TOPOLOGYELEMENT_H

#include "TopologyElementType.h"
#include "Breakdown.h"
#include <set>
#include "vector"

/**
 * @class TopologyElement
 * @brief Represents a generic element in a topology.
 *
 * The TopologyElement class serves as a base class for various types of elements in a topology.
 * It provides basic functionality and attributes that are common to all topology elements.
 */
class TopologyElement {
protected:
    long id; /**< The ID of the topology element. */
    TopologyElementType topology_element_type; /**< The type of the topology element. */
    GeneralTopologyElementType general_topology_element_type; /**< The general type of the topology element. */
    std::set<long> predecessor_element_ids; /**< Set of IDs of the predecessor elements. */
    std::vector<Breakdown*> breakdowns; /**< List of breakdown periods associated with the element. */

public:
    /**
     * @brief Constructs a TopologyElement object with the given ID.
     * @param id The ID of the topology element.
     */
    explicit TopologyElement(long id);

    /**
     * @brief Destructor for the TopologyElement class.
     *
     * This is a pure virtual destructor, making TopologyElement an abstract class.
     */
    virtual ~TopologyElement() = 0;

    /**
     * @brief Returns the ID of the topology element.
     * @return The ID of the topology element.
     */
    [[nodiscard]] long getId() const;

    /**
     * @brief Returns the type of the topology element.
     * @return The type of the topology element.
     */
    TopologyElementType getTopologyElementType();

    /**
     * @brief Returns the general type of the topology element.
     * @return The general type of the topology element.
     */
    GeneralTopologyElementType getGeneralTopologyElementType();

    /**
     * @brief Returns a set of IDs of the predecessor elements.
     * @return A set of IDs of the predecessor elements.
     */
    std::set<long> getPredecessorIds();

    /**
     * @brief Adds a predecessor element ID to the set of predecessor IDs.
     * @param element_id The ID of the predecessor element to add.
     */
    void addPredecessorId(long element_id);

    /**
     * @brief Retrieves the list of breakdown periods associated with the element.
     * @return A vector of Breakdown pointers representing breakdown periods.
     */
    std::vector<Breakdown*> getBreakdowns();

    /**
     * @brief Adds a breakdown period to the list of associated breakdowns.
     * @param breakdown A pointer to a Breakdown object representing a breakdown period.
     */
    void addBreakdown(Breakdown* breakdown);
};

#endif //SCHEDULING_TOPOLOGYELEMENT_H
