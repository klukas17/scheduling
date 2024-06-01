//
// Created by mihael on 5/31/24.
//

#ifndef SGEGRAMMAR_H
#define SGEGRAMMAR_H
#include <map>
#include <vector>

#include "SGENodeTypes.h"


class SGEGrammar {
public:
    std::map<SGENodeType, std::vector<SGENodeType>> productions;
    SGEGrammar();
};



#endif //SGEGRAMMAR_H
