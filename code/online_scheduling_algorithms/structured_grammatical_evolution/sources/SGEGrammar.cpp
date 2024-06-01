//
// Created by mihael on 5/31/24.
//

#include "SGEGrammar.h"

SGEGrammar::SGEGrammar() {
    productions[SGE_SYMBOL] = {
        SGE_TERMINAL,
        SGE_NONTERMINAL
    };
    productions[SGE_TERMINAL] = {
        SGE_CONST,
        SGE_PARAM
    };
    productions[SGE_NONTERMINAL] = {
        SGE_UNARY_MINUS,
        SGE_PLUS,
        SGE_MINUS,
        SGE_TIMES,
        SGE_DIVIDE,
        SGE_SQUARE,
        SGE_ROOT,
        SGE_BRANCH
    };
}
