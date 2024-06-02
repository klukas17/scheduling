//
// Created by mihael on 6/2/24.
//

#ifndef GBGPPROGRAM_H
#define GBGPPROGRAM_H
#include <map>
#include <set>
#include <string>
#include <vector>

#include "GBGPNode.h"


class GBGPProgram {
public:
    std::map<int, GBGPNode*> nodes;
    std::map<int, double> constant_map;
    std::set<int> free_node_ids;
    std::vector<std::string> inputs;
    std::map<int, std::set<int>> from_nodes;
    std::map<int, std::set<int>> to_nodes;
    int output_node_id;
    GBGPProgram(
        std::map<int, GBGPNode*> nodes,
        std::map<int, double> constant_map,
        std::set<int> free_node_ids,
        std::vector<std::string> inputs,
        std::map<int, std::set<int>> from_nodes,
        std::map<int, std::set<int>> to_nodes,
        int output_node_id
    );
    ~GBGPProgram();
    GBGPProgram* copy();
    double executeProgram(std::map<std::string, double> params);
    double executeSubProgram(int node_id, std::map<int, double>& values, std::map<std::string, double>& params);
};



#endif //GBGPPROGRAM_H
