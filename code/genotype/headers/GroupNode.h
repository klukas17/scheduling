//
// Created by mihael on 01/05/23.
//

/**
 * @file GroupNode.h
 * @brief Defines the GroupNode class for representing a group node within an individual's genotype.
 */

#ifndef SCHEDULING_GROUPNODE_H
#define SCHEDULING_GROUPNODE_H

#include "GenotypeNode.h"
#include "vector"

/**
 * @class GroupNode
 * @brief Represents a group node within an individual's genotype.
 *
 * The GroupNode class is derived from the GenotypeNode class and represents a node in an individual's genotype that
 * encompasses a group of nodes. It includes attributes to store the group's body, which consists of contained nodes.
 */
class GroupNode : public GenotypeNode {
protected:
    std::vector<GenotypeNode*> body; /**< Vector of nodes contained within the group. */
public:
    /**
     * @brief Constructs a GroupNode object with the provided identifier.
     * @param id The identifier for the group node.
     */
    explicit GroupNode(long id);

    /**
     * @brief Virtual destructor for the GroupNode class.
     */
    ~GroupNode() override = 0;

    /**
     * @brief Retrieves the vector of nodes contained within the group.
     * @return A vector containing pointers to the contained nodes.
     */
    std::vector<GenotypeNode*> getBody();

    /**
     * @brief Adds a node to the body of the group.
     * @param node A pointer to the node to be added to the group's body.
     */
    void addNodeToBody(GenotypeNode* node);
};

#endif //SCHEDULING_GROUPNODE_H
