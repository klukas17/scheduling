//
// Created by mihael on 5/30/24.
//

#include "GEPhenotypeNode.h"

#include "GEPhenotypeNodeConst.h"
#include "GEPhenotypeNodeParam.h"

#include <cmath>

GEPhenotypeNode::GEPhenotypeNode(int node_id, GENodeType node_type) {
    this->node_id = node_id;
    this->node_type = node_type;
}

GEPhenotypeNode::~GEPhenotypeNode() {
    for (auto & child : children) {
        delete child;
    }
}

GEPhenotypeNode* GEPhenotypeNode::copy() {
    auto new_node = new GEPhenotypeNode(node_id, node_type);
    for (auto child : children) {
        new_node->children.push_back(child->copy());
    }
    return new_node;
}

void GEPhenotypeNode::collectConstants(std::map<int, double>& constants) {
    for (auto child : children) {
        child->collectConstants(constants);
    }
}

double GEPhenotypeNode::eval(std::map<std::string, double>& params) {

    switch (node_type) {

    case GE_SYMBOL:
    case GE_TERMINAL:
    case GE_NONTERMINAL:
    case GE_CONST:
    case GE_PARAM:
        {
            return children[0]->eval(params);
        }

    case GE_UNARY_MINUS:
        {
            auto arg = children[0]->eval(params);
            return -arg;
        }

    case GE_PLUS:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            return arg1 + arg2;
        }

    case GE_MINUS:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            return arg1 - arg2;
        }

    case GE_TIMES:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            auto res = arg1 * arg2;
            return std::isinf(res) ? 1 : res;
        }

    case GE_DIVIDE:
        {
            auto arg2 = children[1]->eval(params);
            if (std::abs(arg2) <= 1e-6) return 1;
            auto arg1 = children[0]->eval(params);
            auto res = arg1 / arg2;
            return std::isinf(res) ? 1 : res;
        }

    case GE_SQUARE:
        {
            auto arg = children[0]->eval(params);
            auto res = std::pow(arg, 2);
            return std::isinf(res) ? 1 : res;
        }

    case GE_ROOT:
        {
            auto arg = children[0]->eval(params);
            return std::sqrt(std::abs(arg));
        }

    case GE_BRANCH:
        {
            auto arg1 = children[0]->eval(params);
            if (arg1 >= 0) return children[1]->eval(params);
            return children[2]->eval(params);
        }

    case GE_LEAF_CONST:
        {
            return dynamic_cast<GEPhenotypeNodeConst*>(this)->constant;
        }

    case GE_LEAF_PARAM:
        {
            return params[dynamic_cast<GEPhenotypeNodeParam*>(this)->param];
        }

    }
}
