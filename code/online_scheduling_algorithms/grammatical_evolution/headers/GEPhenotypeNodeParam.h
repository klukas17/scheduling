//
// Created by mihael on 5/31/24.
//

#ifndef GEPHENOTYPENODEPARAM_H
#define GEPHENOTYPENODEPARAM_H
#include "GEPhenotypeNode.h"


class GEPhenotypeNodeParam final : public GEPhenotypeNode {
public:
    std::string param;
    GEPhenotypeNodeParam(int node_id, GENodeType node_type, std::string param);
    ~GEPhenotypeNodeParam() override;
    GEPhenotypeNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //GEPHENOTYPENODEPARAM_H
