//
// Created by mihael on 5/20/24.
//

#ifndef CONSTANTPROGRAMMINGSERIALIZATIONOPERATOR_H
#define CONSTANTPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "SerializationOperator.h"


class ConstantProgrammingSerializationOperator final : public SerializationOperator {
public:
    ConstantProgrammingSerializationOperator();
    ~ConstantProgrammingSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //CONSTANTPROGRAMMINGSERIALIZATIONOPERATOR_H
