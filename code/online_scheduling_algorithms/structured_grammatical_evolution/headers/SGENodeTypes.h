//
// Created by mihael on 5/31/24.
//

#ifndef SGENODETYPES_H
#define SGENODETYPES_H

enum SGENodeType {
    SGE_SYMBOL,
    SGE_TERMINAL,
    SGE_NONTERMINAL,
    SGE_CONST,
    SGE_PARAM,
    SGE_UNARY_MINUS,
    SGE_PLUS,
    SGE_MINUS,
    SGE_TIMES,
    SGE_DIVIDE,
    SGE_SQUARE,
    SGE_ROOT,
    SGE_BRANCH,
    SGE_LEAF_CONST,
    SGE_LEAF_PARAM
};

#endif //SGENODETYPES_H