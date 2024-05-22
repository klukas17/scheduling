//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEPARAM_H
#define TBGPNODEPARAM_H
#include <string>

#include "TBGPNode.h"


class TBGPNodeParam final : public TBGPNode {
public:
    std::string param;
    TBGPNodeParam();
    ~TBGPNodeParam() override;
    TBGPNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //TBGPNODEPARAM_H
