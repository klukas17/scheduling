//
// Created by mihael on 6/1/24.
//

#ifndef SGEPHENOTYPENODEPARAM_H
#define SGEPHENOTYPENODEPARAM_H
#include "SGEPhenotypeNode.h"


class SGEPhenotypeNodeParam final : public SGEPhenotypeNode {
public:
    std::string param;
    SGEPhenotypeNodeParam(int node_id, int depth, SGENodeType node_type, std::string param);
    ~SGEPhenotypeNodeParam() override;
    SGEPhenotypeNode* copy() override;
    double eval(std::map<std::string, double>& params) override;
};



#endif //SGEPHENOTYPENODEPARAM_H
