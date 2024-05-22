//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEUNARYMINUS_H
#define TBGPNODEUNARYMINUS_H
#include "TBGPNode.h"


class TBGPNodeUnaryMinus final : public TBGPNode {
public:
    TBGPNode* operand_node;
    TBGPNodeUnaryMinus();
    ~TBGPNodeUnaryMinus() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODEUNARYMINUS_H
