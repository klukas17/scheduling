//
// Created by mihael on 30/04/23.
//

/**
 * @file SerialGroupNode.cpp
 * @brief Implements the member functions of the SerialGroupNode class.
 */

#include "SerialGroupNode.h"

SerialGroupNode::SerialGroupNode(long id) : GroupNode(id) {
    this->node_type = SERIAL_GROUP_NODE;
}