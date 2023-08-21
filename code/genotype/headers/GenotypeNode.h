//
// Created by mihael on 29/04/23.
//

/**
 * @file GenotypeNode.h
 * @brief Defines the GenotypeNode class for representing a node within an individual's genotype.
 */

#ifndef SCHEDULING_GENOTYPENODE_H
#define SCHEDULING_GENOTYPENODE_H

#include "NodeType.h"
#include "vector"
#include "set"

/**
 * @class GenotypeNode
 * @brief Represents a node within an individual's genotype.
 *
 * The GenotypeNode class serves as a base class for representing nodes within an individual's genotype in a scheduling system.
 * It includes attributes to store node information, such as identifiers, node types, processing order, and predecessors.
 */
class GenotypeNode {
protected:
    long id; /**< Identifier for the node. */
    NodeType node_type; /**< Type of the node. */
    GeneralNodeType general_node_type; /**< General category of the node type. */
    std::vector<long> step_processing_order; /**< Order of processing steps for the node. */
    std::set<long> predecessor_node_ids; /**< Set of identifiers for predecessor nodes. */
public:
    /**
     * @brief Constructs a GenotypeNode object with the provided identifier.
     * @param id The identifier for the node.
     */
    explicit GenotypeNode(long id);

    /**
     * @brief Virtual destructor for the GenotypeNode class.
     */
    virtual ~GenotypeNode() = 0;

    /**
     * @brief Retrieves the identifier for the node.
     * @return The identifier for the node.
     */
    [[nodiscard]] long getId() const;

    /**
     * @brief Retrieves the type of the node.
     * @return The type of the node.
     */
    NodeType getNodeType();

    /**
     * @brief Retrieves the general category of the node type.
     * @return The general category of the node type.
     */
    GeneralNodeType getGeneralNodeType();

    /**
     * @brief Retrieves the order of processing steps for the node.
     * @return A vector containing step identifiers in the processing order.
     */
    std::vector<long> getStepProcessingOrder();

    /**
     * @brief Adds a processing step identifier to the processing order.
     * @param step_id The identifier of the processing step to be added.
     */
    void addStep(long step_id);

    /**
     * @brief Retrieves the set of identifiers for predecessor nodes.
     * @return A set containing identifiers of predecessor nodes.
     */
    std::set<long> getPredecessorIds();

    /**
     * @brief Adds a predecessor node identifier to the set.
     * @param node_id The identifier of the predecessor node to be added.
     */
    void addPredecessorId(long node_id);
};

#endif //SCHEDULING_GENOTYPENODE_H
