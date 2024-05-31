//
// Created by mihael on 5/31/24.
//

#ifndef GEPHENOTYPENODECONST_H
#define GEPHENOTYPENODECONST_H
#include "GEPhenotypeNode.h"


class GEPhenotypeNodeConst final : public GEPhenotypeNode {
public:
    double constant;
    GEPhenotypeNodeConst(int node_id, GENodeType node_type, double constant);
    ~GEPhenotypeNodeConst() override;
    GEPhenotypeNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
    void collectConstants(std::map<int, double>& constants) override;
};



#endif //GEPHENOTYPENODECONST_H
