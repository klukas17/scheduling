//
// Created by mihael on 5/31/24.
//

#include "GEPhenotypeNodeParam.h"

#include <utility>

GEPhenotypeNodeParam::GEPhenotypeNodeParam(int node_id, GENodeType node_type, std::string param) : GEPhenotypeNode(node_id, node_type) {
    this->param = std::move(param);
}

GEPhenotypeNodeParam::~GEPhenotypeNodeParam() = default;

GEPhenotypeNode* GEPhenotypeNodeParam::copy() {
    return new GEPhenotypeNodeParam(node_id, node_type, param);
}

double GEPhenotypeNodeParam::eval(std::map<std::string, double>& params) {
    return params[param];
}
