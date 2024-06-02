//
// Created by mihael on 5/29/24.
//

#include "GEPPhenotypeNode.h"
#include <cmath>
#include <utility>

GEPPhenotypeNode::GEPPhenotypeNode(
    int node_id,
    GEPNodeType node_type,
    std::map<int, double> constant_map,
    std::map<int, std::string> param_map
) {
    this->node_id = node_id;
    this->node_type = node_type;
    this->constant_map = std::move(constant_map);
    this->param_map = std::move(param_map);
}

GEPPhenotypeNode::~GEPPhenotypeNode() {
    for (auto & i : children) {
        delete i;
    }
}

double GEPPhenotypeNode::eval(std::map<std::string, double>& params) {

    switch (node_type) {

    case GEP_CONST:
        {
            return constant_map[node_id];
        }

    case GEP_PARAM:
        {
            return params[param_map[node_id]];
        }

    case GEP_UNARY_MINUS:
        {
            auto arg = children[0]->eval(params);
            return -arg;
        }

    case GEP_PLUS:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            return arg1 + arg2;
        }

    case GEP_MINUS:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            return arg1 - arg2;
        }

    case GEP_TIMES:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            auto res = arg1 * arg2;
            return std::isinf(res) ? 1 : res;
        }

    case GEP_DIVIDE:
        {
            auto arg2 = children[1]->eval(params);
            if (std::abs(arg2) <= 1e-6) return 1;
            auto arg1 = children[0]->eval(params);
            auto res = arg1 / arg2;
            return std::isinf(res) ? 1 : res;
        }

    case GEP_SQUARE:
        {
            auto arg = children[0]->eval(params);
            auto res = std::pow(arg, 2);
            return std::isinf(res) ? 1 : res;
        }

    case GEP_ROOT:
        {
            auto arg = children[0]->eval(params);
            return std::sqrt(std::abs(arg));
        }

    case GEP_BRANCH:
        {
            auto arg1 = children[0]->eval(params);
            if (arg1 >= 0) return children[1]->eval(params);
            return children[2]->eval(params);
        }

    }
}

GEPPhenotypeNode* GEPPhenotypeNode::copy() {
    auto new_node = new GEPPhenotypeNode(node_id, node_type, constant_map, param_map);
    for (auto child : children) {
        new_node->children.push_back(child->copy());
    }
    return new_node;
}
