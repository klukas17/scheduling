//
// Created by mihael on 5/30/24.
//

#include "GEGrammar.h"

GEGrammar::GEGrammar() {
    productions[GE_SYMBOL] = {
        GE_TERMINAL,
        GE_NONTERMINAL
    };
    productions[GE_TERMINAL] = {
        GE_CONST,
        GE_PARAM
    };
    productions[GE_NONTERMINAL] = {
        GE_UNARY_MINUS,
        GE_PLUS,
        GE_MINUS,
        GE_TIMES,
        GE_DIVIDE,
        GE_SQUARE,
        GE_ROOT,
        GE_BRANCH
    };
}
