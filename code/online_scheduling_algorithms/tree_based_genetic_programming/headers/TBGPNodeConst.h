//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODECONST_H
#define TBGPNODECONST_H
#include "TBGPNode.h"


class TBGPNodeConst final : public TBGPNode {
public:
    double constant;
    TBGPNodeConst();
    ~TBGPNodeConst() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODECONST_H
