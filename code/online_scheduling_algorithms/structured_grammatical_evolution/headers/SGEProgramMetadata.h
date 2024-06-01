//
// Created by mihael on 5/31/24.
//

#ifndef SGEPROGRAMMETADATA_H
#define SGEPROGRAMMETADATA_H

#include <map>
#include <string>
#include <vector>

#include "SGENodeTypes.h"

class SGEProgramMetadata {
public:
    int max_depth;
    std::vector<std::string> inputs;
    std::map<SGENodeType, int> max_number_of_occurences;
    std::map<SGENodeType, int> possible_values;
    SGEProgramMetadata(int max_depth, std::vector<std::string> inputs);
    ~SGEProgramMetadata();
    SGEProgramMetadata* copy();
};



#endif //SGEPROGRAMMETADATA_H
