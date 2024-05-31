//
// Created by mihael on 5/30/24.
//

#ifndef GEGRAMMAR_H
#define GEGRAMMAR_H
#include <map>
#include <vector>

#include "GENodeTypes.h"


class GEGrammar {
public:
    std::map<GENodeType, std::vector<GENodeType>> productions;
    GEGrammar();
};



#endif //GEGRAMMAR_H
