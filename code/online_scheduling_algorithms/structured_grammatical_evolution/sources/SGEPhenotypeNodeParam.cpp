//
// Created by mihael on 6/1/24.
//

#include "SGEPhenotypeNodeParam.h"

#include <utility>

SGEPhenotypeNodeParam::SGEPhenotypeNodeParam(int node_id, int depth, SGENodeType node_type, std::string param) : SGEPhenotypeNode(node_id, depth, node_type) {
    this->param = std::move(param);
}

SGEPhenotypeNodeParam::~SGEPhenotypeNodeParam() = default;

SGEPhenotypeNode* SGEPhenotypeNodeParam::copy() {
    return new SGEPhenotypeNodeParam(node_id, depth, node_type, param);
}

double SGEPhenotypeNodeParam::eval(std::map<std::string, double>& params) {
    return params[param];
}


