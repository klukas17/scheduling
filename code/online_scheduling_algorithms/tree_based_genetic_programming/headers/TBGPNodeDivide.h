//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEDIVIDE_H
#define TBGPNODEDIVIDE_H
#include "TBGPNode.h"


class TBGPNodeDivide final : public TBGPNode {
public:
    TBGPNode* dividend_node;
    TBGPNode* divisor_node;
    TBGPNodeDivide();
    ~TBGPNodeDivide() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODEDIVIDE_H
