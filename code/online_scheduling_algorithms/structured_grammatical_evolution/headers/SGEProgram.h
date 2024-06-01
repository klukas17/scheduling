//
// Created by mihael on 5/31/24.
//

#ifndef SGEPROGRAM_H
#define SGEPROGRAM_H

#include "SGEPhenotypeNode.h"
#include "SGEProgramMetadata.h"


class SGEProgram {
public:
    SGEProgramMetadata* metadata;
    std::vector<int> symbol_values;
    std::vector<int> terminal_values;
    std::vector<int> nonterminal_values;
    std::vector<int> param_values;
    SGEPhenotypeNode* phenotype_root_node;
    SGEProgram(
        SGEProgramMetadata* metadata,
        std::vector<int> symbol_values,
        std::vector<int> terminal_values,
        std::vector<int> nonterminal_values,
        std::vector<int> param_values
    );
    ~SGEProgram();
    SGEProgram* copy();
    std::map<int, double> collectAllConstants();
    double executeProgram(std::map<std::string, double> params);
};



#endif //SGEPROGRAM_H
