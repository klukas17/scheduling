//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEDEPTHADJUSTER_H
#define TBGPNODEDEPTHADJUSTER_H
#include "TreeBasedGeneticProgramming.h"


class TBGPNodeDepthAdjuster {
    static void adjustHeightForNode(TBGPNode* node);
    static void adjustMaxDepthForNode(TBGPNode* node, int max_depth);
public:
    static void adjustDepths(TreeBasedGeneticProgramming* tbgp, int max_depth);
};



#endif //TBGPNODEDEPTHADJUSTER_H
