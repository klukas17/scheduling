//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODECOLLECTOR_H
#define TBGPNODECOLLECTOR_H
#include <vector>

#include "TBGPNode.h"
#include "TreeBasedGeneticProgramming.h"


class TBGPNodeCollector {
    static void traverseTree(TBGPNode* node, int max_height, std::vector<TBGPNode*>& collection);
public:
    static std::vector<TBGPNode*> collect(TreeBasedGeneticProgramming* tbgp, int max_height);
};



#endif //TBGPNODECOLLECTOR_H
