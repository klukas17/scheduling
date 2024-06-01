//
// Created by mihael on 6/1/24.
//

#ifndef SGEPHENOTYPENODECONST_H
#define SGEPHENOTYPENODECONST_H
#include "SGEPhenotypeNode.h"


class SGEPhenotypeNodeConst final : public SGEPhenotypeNode {
public:
    double constant;
    SGEPhenotypeNodeConst(int node_id, int depth, SGENodeType node_type, double constant);
    ~SGEPhenotypeNodeConst() override;
    SGEPhenotypeNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
    void collectConstants(std::map<int, double>& constants) override;
};



#endif //SGEPHENOTYPENODECONST_H
