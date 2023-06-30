//
// Created by mihael on 29/04/23.
//

/**
 * @file TopologyElementType.h
 * @brief Defines enumerations for different types of topology elements.
 */

#ifndef SCHEDULING_TOPOLOGYELEMENTTYPE_H
#define SCHEDULING_TOPOLOGYELEMENTTYPE_H

/**
 * @enum TopologyElementType
 * @brief Represents the type of a topology element.
 *
 * The TopologyElementType enum represents the type of a topology element, including abstract elements,
 * machine elements, serial group elements, parallel group elements, route group elements, and open group elements.
 */
enum TopologyElementType {
    ABSTRACT_TOPOLOGY_ELEMENT,         /**< Abstract topology element type */
    MACHINE_TOPOLOGY_ELEMENT,          /**< Machine topology element type */
    SERIAL_GROUP_TOPOLOGY_ELEMENT,     /**< Serial group topology element type */
    PARALLEL_GROUP_TOPOLOGY_ELEMENT,   /**< Parallel group topology element type */
    ROUTE_GROUP_TOPOLOGY_ELEMENT,      /**< Route group topology element type */
    OPEN_GROUP_TOPOLOGY_ELEMENT        /**< Open group topology element type */
};

/**
 * @enum GeneralTopologyElementType
 * @brief Represents the general type of a topology element.
 *
 * The GeneralTopologyElementType enum represents the general type of a topology element, including
 * abstract elements, machine elements, and group elements.
 */
enum GeneralTopologyElementType {
    ABSTRACT_GENERAL_TOPOLOGY_ELEMENT, /**< Abstract general topology element type */
    MACHINE_GENERAL_TOPOLOGY_ELEMENT,  /**< Machine general topology element type */
    GROUP_GENERAL_TOPOLOGY_ELEMENT     /**< Group general topology element type */
};

#endif //SCHEDULING_TOPOLOGYELEMENTTYPE_H
