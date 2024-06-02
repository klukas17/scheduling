//
// Created by mihael on 5/31/24.
//

#include "SGEPhenotypeNode.h"
#include <cmath>

#include "SGEPhenotypeNodeConst.h"
#include "SGEPhenotypeNodeParam.h"

SGEPhenotypeNode::SGEPhenotypeNode(int node_id, int depth, SGENodeType node_type) {
    this->node_id = node_id;
    this->depth = depth;
    this->node_type = node_type;
}

SGEPhenotypeNode::~SGEPhenotypeNode() {
    for (auto & child : children) {
        delete child;
    }
}

SGEPhenotypeNode* SGEPhenotypeNode::copy() {
    auto new_node = new SGEPhenotypeNode(node_id, depth, node_type);
    for (auto child : children) {
        new_node->children.push_back(child->copy());
    }
    return new_node;
}

void SGEPhenotypeNode::collectConstants(std::map<int, double>& constants) {
    for (auto child : children) {
        child->collectConstants(constants);
    }
}

double SGEPhenotypeNode::eval(std::map<std::string, double>& params) {
    switch (node_type) {

    case SGE_SYMBOL:
    case SGE_TERMINAL:
    case SGE_NONTERMINAL:
    case SGE_CONST:
    case SGE_PARAM:
        {
            return children[0]->eval(params);
        }

    case SGE_UNARY_MINUS:
        {
            auto arg = children[0]->eval(params);
            return -arg;
        }

    case SGE_PLUS:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            return arg1 + arg2;
        }

    case SGE_MINUS:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            return arg1 - arg2;
        }

    case SGE_TIMES:
        {
            auto arg1 = children[0]->eval(params);
            auto arg2 = children[1]->eval(params);
            auto res = arg1 * arg2;
            return std::isinf(res) ? 1 : res;
        }

    case SGE_DIVIDE:
        {
            auto arg2 = children[1]->eval(params);
            if (std::abs(arg2) <= 1e-6) return 1;
            auto arg1 = children[0]->eval(params);
            auto res = arg1 / arg2;
            return std::isinf(res) ? 1 : res;
        }

    case SGE_SQUARE:
        {
            auto arg = children[0]->eval(params);
            auto res = std::pow(arg, 2);
            return std::isinf(res) ? 1 : res;
        }

    case SGE_ROOT:
        {
            auto arg = children[0]->eval(params);
            return std::sqrt(std::abs(arg));
        }

    case SGE_BRANCH:
        {
            auto arg1 = children[0]->eval(params);
            if (arg1 >= 0) return children[1]->eval(params);
            return children[2]->eval(params);
        }

    case SGE_LEAF_CONST:
        {
            return dynamic_cast<SGEPhenotypeNodeConst*>(this)->constant;
        }

    case SGE_LEAF_PARAM:
        {
            return params[dynamic_cast<SGEPhenotypeNodeParam*>(this)->param];
        }

    }
}

