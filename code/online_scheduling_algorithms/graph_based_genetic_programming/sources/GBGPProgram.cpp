//
// Created by mihael on 6/2/24.
//

#include "GBGPProgram.h"

#include <ranges>
#include <utility>
#include <cmath>

GBGPProgram::GBGPProgram(
    std::map<int, GBGPNode*> nodes,
    std::map<int, double> constant_map,
    std::set<int> free_node_ids,
    std::vector<std::string> inputs,
    std::map<int, std::set<int>> from_nodes,
    std::map<int, std::set<int>> to_nodes,
    int output_node_id
) {
    this->nodes = std::move(nodes);
    this->constant_map = std::move(constant_map);
    this->free_node_ids = std::move(free_node_ids);
    this->inputs = std::move(inputs);
    this->from_nodes = std::move(from_nodes);
    this->to_nodes = std::move(to_nodes);
    this->output_node_id = output_node_id;
}

GBGPProgram::~GBGPProgram() {
    for (auto node : nodes | std::ranges::views::values) {
        delete node;
    }
}

GBGPProgram* GBGPProgram::copy() {
    std::map<int, GBGPNode*> nodes_copy;
    for (auto [node_id, node] : nodes) {
        nodes_copy[node_id] = node->copy();
    }
    return new GBGPProgram(
        nodes_copy,
        constant_map,
        free_node_ids,
        inputs,
        from_nodes,
        to_nodes,
        output_node_id
    );
}

double GBGPProgram::executeProgram(std::map<std::string, double> params) {
    std::map<int, double> values;
    for (int i = 0; i < inputs.size(); i++) {
        values[i] = params[inputs[i]];
    }
    return executeSubProgram(output_node_id, values, params);
}

double GBGPProgram::executeSubProgram(int node_id, std::map<int, double>& values, std::map<std::string, double>& params) {
    if (values.contains(node_id)) {
        return values[node_id];
    }

    auto node = nodes[node_id];
    double value;

    switch(node->node_type) {

    case GBGP_CONST:
        {
            value = constant_map[node->node_id];
            break;
        }

    case GBGP_UNARY_MINUS:
        {
            auto arg = executeSubProgram(
                node->first_predecessor_index,
                values,
                params
            );
            value = -arg;
            break;
        }

    case GBGP_PLUS:
        {
            auto arg1 = executeSubProgram(
                node->first_predecessor_index,
                values,
                params
            );
            auto arg2 = executeSubProgram(
                node->second_predecessor_index,
                values,
                params
            );
            value = arg1 + arg2;
            break;
        }

    case GBGP_MINUS:
        {
            auto arg1 = executeSubProgram(
                node->first_predecessor_index,
                values,
                params
            );
            auto arg2 = executeSubProgram(
                node->second_predecessor_index,
                values,
                params
            );
            value = arg1 - arg2;
            break;
        }

    case GBGP_TIMES:
        {
            auto arg1 = executeSubProgram(
                node->first_predecessor_index,
                values,
                params
            );
            auto arg2 = executeSubProgram(
                node->second_predecessor_index,
                values,
                params
            );
            auto res = arg1 * arg2;
            value = std::isinf(res) ? 1 : res;
            break;
        }

    case GBGP_DIVIDE:
        {
            auto arg2 = executeSubProgram(
                node->second_predecessor_index,
                values,
                params
            );
            if (std::abs(arg2) <= 1e-6) {
                value = 1;
            } else {
                auto arg1 = executeSubProgram(
                   node->first_predecessor_index,
                   values,
                   params
               );
                auto res = arg1 / arg2;
                value = std::isinf(res) ? 1 : res;
            }
            break;
        }

    case GBGP_SQUARE:
        {
            auto arg1 = executeSubProgram(
                node->first_predecessor_index,
                values,
                params
            );
            auto res = std::pow(arg1, 2);
            value = std::isinf(res) ? 1 : res;
            break;
        }

    case GBGP_ROOT:
        {
            auto arg1 = executeSubProgram(
                node->first_predecessor_index,
                values,
                params
            );
            value = std::sqrt(std::abs(arg1));
            break;
        }

    case GBGP_BRANCH:
        {
            auto arg1 = executeSubProgram(
                node->first_predecessor_index,
                values,
                params
            );
            if (arg1 >= 0) {
                auto arg2 = executeSubProgram(
                    node->second_predecessor_index,
                    values,
                    params
                );
                value = arg2;
            } else {
                auto arg3 = executeSubProgram(
                    node->third_predecessor_index,
                    values,
                    params
                );
                value = arg3;
            }
            break;
        }

    }

    values[node_id] = value;
    return value;
}
