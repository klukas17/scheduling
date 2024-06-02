//
// Created by mihael on 6/1/24.
//

#ifndef GBGPNODE_H
#define GBGPNODE_H
#include "GBGPNodeTypes.h"


class GBGPNode {
public:
    int node_id;
    GBGPNodeType node_type;
    int first_predecessor_index;
    int second_predecessor_index;
    int third_predecessor_index;
    GBGPNode(int node_id, GBGPNodeType node_type, int first_predecessor_index, int second_predecessor_index, int third_predecessor_index);
    ~GBGPNode();
    GBGPNode* copy();
};



#endif //GBGPNODE_H
