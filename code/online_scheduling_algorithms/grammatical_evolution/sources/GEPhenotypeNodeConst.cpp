//
// Created by mihael on 5/31/24.
//

#include "GEPhenotypeNodeConst.h"

GEPhenotypeNodeConst::GEPhenotypeNodeConst(int node_id, GENodeType node_type, double constant) : GEPhenotypeNode(node_id, node_type) {
    this->constant = constant;
}

GEPhenotypeNodeConst::~GEPhenotypeNodeConst() = default;

GEPhenotypeNode* GEPhenotypeNodeConst::copy() {
    return new GEPhenotypeNodeConst(node_id, node_type, constant);
}

void GEPhenotypeNodeConst::collectConstants(std::map<int, double>& constants) {
    constants[node_id] = constant;
}

double GEPhenotypeNodeConst::eval(std::map<std::string, double>& params) {
    return constant;
}
