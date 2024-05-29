//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeParam.h"

TBGPNodeParam::TBGPNodeParam() {
    this->node_type = TBGP_PARAM;
    param = "";
}

TBGPNodeParam::~TBGPNodeParam() = default;

TBGPNode* TBGPNodeParam::copy() {
    auto copy = new TBGPNodeParam();
    copy->param = param;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}


double TBGPNodeParam::eval(std::map<std::string, double>& params) {
    return params[param];
}
