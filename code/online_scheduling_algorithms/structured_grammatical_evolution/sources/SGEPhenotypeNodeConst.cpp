//
// Created by mihael on 6/1/24.
//

#include "SGEPhenotypeNodeConst.h"

SGEPhenotypeNodeConst::SGEPhenotypeNodeConst(int node_id, int depth, SGENodeType node_type, double constant) : SGEPhenotypeNode(node_id, depth, node_type) {
    this->constant = constant;
}

SGEPhenotypeNodeConst::~SGEPhenotypeNodeConst() = default;

SGEPhenotypeNode* SGEPhenotypeNodeConst::copy() {
    return new SGEPhenotypeNodeConst(node_id, depth, node_type, constant);
}

void SGEPhenotypeNodeConst::collectConstants(std::map<int, double>& constants) {
    constants[node_id] = constant;
}

double SGEPhenotypeNodeConst::eval(std::map<std::string, double>& params) {
    return constant;
}

