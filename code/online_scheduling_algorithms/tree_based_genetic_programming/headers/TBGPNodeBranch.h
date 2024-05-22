//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEBRANCH_H
#define TBGPNODEBRANCH_H
#include "TBGPNode.h"


class TBGPNodeBranch final : public TBGPNode {
public:
    TBGPNode* if_node;
    TBGPNode* then_node;
    TBGPNode* else_node;
    TBGPNodeBranch();
    ~TBGPNodeBranch() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODEBRANCH_H
