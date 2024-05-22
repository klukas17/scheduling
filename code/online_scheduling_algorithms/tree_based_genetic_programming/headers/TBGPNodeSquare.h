//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODESQUARE_H
#define TBGPNODESQUARE_H
#include "TBGPNode.h"


class TBGPNodeSquare final : public TBGPNode {
public:
    TBGPNode* base_node;
    TBGPNodeSquare();
    ~TBGPNodeSquare() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODESQUARE_H
