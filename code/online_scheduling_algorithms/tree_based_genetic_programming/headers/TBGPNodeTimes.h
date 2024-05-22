//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODETIMES_H
#define TBGPNODETIMES_H
#include "TBGPNode.h"


class TBGPNodeTimes final : public TBGPNode {
public:
    TBGPNode* first_factor_node;
    TBGPNode* second_factor_node;
    TBGPNodeTimes();
    ~TBGPNodeTimes() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODETIMES_H
