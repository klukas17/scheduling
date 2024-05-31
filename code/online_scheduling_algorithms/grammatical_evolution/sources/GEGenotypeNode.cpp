//
// Created by mihael on 5/30/24.
//

#include "GEGenotypeNode.h"

GEGenotypeNode::GEGenotypeNode(int node_id, int codon_value) {
    this->node_id = node_id;
    this->codon_value = codon_value;
}

GEGenotypeNode::~GEGenotypeNode() = default;

GEGenotypeNode* GEGenotypeNode::copy() {
    return new GEGenotypeNode(node_id, codon_value);
}

