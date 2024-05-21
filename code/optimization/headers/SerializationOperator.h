//
// Created by mihael on 5/20/24.
//

#ifndef SERIALIZATIONOPERATOR_H
#define SERIALIZATIONOPERATOR_H
#include <string>
#include <vector>

#include "Genotype.h"


class SerializationOperator {
public:
    virtual std::vector<std::string> serialize(Genotype* genotype) = 0;
    virtual Genotype* deserialize(std::vector<std::string> representation) = 0;
    virtual ~SerializationOperator() = 0;
};



#endif //SERIALIZATIONOPERATOR_H
