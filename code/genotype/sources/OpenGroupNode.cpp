//
// Created by mihael on 01/05/23.
//

#include "OpenGroupNode.h"

OpenGroupNode::OpenGroupNode(long const id) : GroupNode(id) {
    this->node_type = OPEN_GROUP_NODE;
}