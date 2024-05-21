//
// Created by mihael on 5/20/24.
//

#ifndef RANDOMPROGRAMMINGSERIALIZATIONOPERATOR_H
#define RANDOMPROGRAMMINGSERIALIZATIONOPERATOR_H
#include "SerializationOperator.h"


class RandomProgrammingSerializationOperator final : public SerializationOperator {
public:
    RandomProgrammingSerializationOperator();
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //RANDOMPROGRAMMINGSERIALIZATIONOPERATOR_H
