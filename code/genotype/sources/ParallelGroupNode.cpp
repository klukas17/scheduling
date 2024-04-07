//
// Created by mihael on 01/05/23.
//

#include "ParallelGroupNode.h"

ParallelGroupNode::ParallelGroupNode(long const id) : GroupNode(id) {
    this->node_type = PARALLEL_GROUP_NODE;
}