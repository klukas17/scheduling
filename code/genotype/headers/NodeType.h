//
// Created by mihael on 29/04/23.
//

/**
 * @file NodeType.h
 * @brief Defines enumerations for different types of genotype nodes.
 */

#ifndef SCHEDULING_NODETYPE_H
#define SCHEDULING_NODETYPE_H

/**
 * @enum NodeType
 * @brief Enumerates different types of nodes in a scheduling system.
 *
 * The NodeType enumeration provides constants for categorizing various types of nodes that can exist in a scheduling
 * system, such as machine nodes, group nodes, etc. Each constant represents a distinct node type.
 */
enum NodeType {
    ABSTRACT_NODE,      /**< Represents an abstract node. */
    MACHINE_NODE,       /**< Represents a machine node. */
    SERIAL_GROUP_NODE,  /**< Represents a serial group node. */
    PARALLEL_GROUP_NODE,/**< Represents a parallel group node. */
    ROUTE_GROUP_NODE,   /**< Represents a route group node. */
    OPEN_GROUP_NODE     /**< Represents an open group node. */
};

/**
 * @enum GeneralNodeType
 * @brief Enumerates general categories of node types in a scheduling system.
 *
 * The GeneralNodeType enumeration provides general categories for grouping different types of nodes that can exist
 * in a scheduling system, such as machine nodes and group nodes. Each constant represents a distinct general node type.
 */
enum GeneralNodeType {
    ABSTRACT_GENERAL_NODE, /**< Represents an abstract general node. */
    MACHINE_GENERAL_NODE,  /**< Represents a machine general node. */
    GROUP_GENERAL_NODE     /**< Represents a group general node. */
};

#endif //SCHEDULING_NODETYPE_H

