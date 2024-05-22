//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEMINUS_H
#define TBGPNODEMINUS_H
#include "TBGPNode.h"


class TBGPNodeMinus final : public TBGPNode {
public:
    TBGPNode* minuend_node;
    TBGPNode* subtrahend_node;
    TBGPNodeMinus();
    ~TBGPNodeMinus() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODEMINUS_H
