//
// Created by mihael on 5/29/24.
//

#include "GEPGenotypeNode.h"

GEPGenotypeNode::GEPGenotypeNode(int node_id, GEPNodeType node_type) {
    this->node_id = node_id;
    this->node_type = node_type;
}

GEPGenotypeNode::~GEPGenotypeNode() = default;

GEPGenotypeNode* GEPGenotypeNode::copy() {
    return new GEPGenotypeNode(node_id, node_type);
}
