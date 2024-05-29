//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeConst.h"

TBGPNodeConst::TBGPNodeConst() {
    this->node_type = TBGP_CONST;
    constant = 0;
}

TBGPNodeConst::~TBGPNodeConst() = default;

TBGPNode* TBGPNodeConst::copy() {
    auto copy = new TBGPNodeConst();
    copy->constant = constant;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}


double TBGPNodeConst::eval(std::map<std::string, double>& params) {
    return constant;
}


