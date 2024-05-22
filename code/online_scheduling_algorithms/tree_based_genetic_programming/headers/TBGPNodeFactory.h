//
// Created by mihael on 5/21/24.
//

#ifndef TBGPNODEFACTORY_H
#define TBGPNODEFACTORY_H
#include <vector>

#include "DoubleGenerator.h"
#include "IntegerGenerator.h"
#include "TBGPNode.h"


class TBGPNodeFactory {
    double leaf_const_chance;
    double leaf_param_chance;
    DoubleGenerator* chance_generator;
    DoubleGenerator* constant_generator;
    IntegerGenerator* index_generator;
    std::vector<std::string> inputs;
public:
    static std::vector<TBGPNodeType> inner_node_types;
    TBGPNodeFactory(double leaf_const_chance, double leaf_param_chance, double constant_min, double constant_max);
    void setInputs(std::vector<std::string> inputs);
    TBGPNode* createNode(int max_height);
};



#endif //TBGPNODEFACTORY_H
