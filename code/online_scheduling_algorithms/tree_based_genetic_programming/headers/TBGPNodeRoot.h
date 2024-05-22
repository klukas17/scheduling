//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEROOT_H
#define TBGPNODEROOT_H
#include "TBGPNode.h"


class TBGPNodeRoot final : public TBGPNode {
public:
    TBGPNode* radicand_node;
    TBGPNodeRoot();
    ~TBGPNodeRoot() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODEROOT_H
