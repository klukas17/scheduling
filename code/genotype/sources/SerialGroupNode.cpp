//
// Created by mihael on 30/04/23.
//

#include "SerialGroupNode.h"

SerialGroupNode::SerialGroupNode(long const id) : GroupNode(id) {
    this->node_type = SERIAL_GROUP_NODE;
}