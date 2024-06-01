//
// Created by mihael on 5/31/24.
//

#include "SGEProgramMetadata.h"

#include <cmath>

SGEProgramMetadata::SGEProgramMetadata(int max_depth, std::vector<std::string> inputs) {
    this->max_depth = max_depth;
    this->inputs = std::move(inputs);
    possible_values[SGE_SYMBOL] = 2;
    possible_values[SGE_TERMINAL] = 2;
    possible_values[SGE_NONTERMINAL] = 8;
    possible_values[SGE_PARAM] = this->inputs.size();
    int n = 0;
    for (int i = 0; i < max_depth; i++) {
        n += std::pow(3, i);
    }
    max_number_of_occurences[SGE_SYMBOL] = max_number_of_occurences[SGE_NONTERMINAL] = n;
    max_number_of_occurences[SGE_TERMINAL] = max_number_of_occurences[SGE_PARAM] = std::pow(3, max_depth);
}

SGEProgramMetadata::~SGEProgramMetadata() = default;

SGEProgramMetadata* SGEProgramMetadata::copy() {
    return new SGEProgramMetadata(max_depth, inputs);
}

