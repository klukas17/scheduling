//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODE_H
#define TBGPNODE_H
#include <map>
#include <string>

#include "TBGPNodeType.h"


class TBGPNode {
public:
    int height;
    int max_depth;
    TBGPNode* parent;
    TBGPNodeType node_type;
    explicit TBGPNode();
    virtual ~TBGPNode() = 0;
    virtual TBGPNode* copy() = 0;
    virtual double eval(std::map<std::string, double>& params) = 0;
};



#endif //TBGPNODE_H
