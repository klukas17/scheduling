//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEPLUS_H
#define TBGPNODEPLUS_H
#include "TBGPNode.h"


class TBGPNodePlus final : public TBGPNode {
public:
    TBGPNode* first_summand_node;
    TBGPNode* second_summand_node;
    TBGPNodePlus();
    ~TBGPNodePlus() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODEPLUS_H
