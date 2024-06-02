//
// Created by mihael on 6/1/24.
//

#include "GBGPNode.h"

GBGPNode::GBGPNode(int node_id, GBGPNodeType node_type, int first_predecessor_index, int second_predecessor_index, int third_predecessor_index) {
    this->node_id = node_id;
    this->node_type = node_type;
    this->first_predecessor_index = first_predecessor_index;
    this->second_predecessor_index = second_predecessor_index;
    this->third_predecessor_index = third_predecessor_index;
}

GBGPNode::~GBGPNode() = default;

GBGPNode* GBGPNode::copy() {
    return new GBGPNode(node_id, node_type, first_predecessor_index, second_predecessor_index, third_predecessor_index);
}
