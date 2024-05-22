//
// Created by mihael on 5/21/24.
//

#ifndef TREEBASEDGENETICPROGRAMMING_H
#define TREEBASEDGENETICPROGRAMMING_H
#include "OnlineSchedulingAlgorithm.h"
#include "TBGPNode.h"


class TreeBasedGeneticProgramming final : public OnlineSchedulingAlgorithm {
    TBGPNode* root_node;
public:
    explicit TreeBasedGeneticProgramming(TBGPNode* root_node);
    ~TreeBasedGeneticProgramming() override;
    TBGPNode* getRootNode();
    void setRootNode(TBGPNode* root_node);
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //TREEBASEDGENETICPROGRAMMING_H
