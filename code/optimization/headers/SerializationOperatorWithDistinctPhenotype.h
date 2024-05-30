//
// Created by mihael on 5/29/24.
//

#ifndef SERIALIZATIONOPERATORWITHDISTINCTPHENOTYPE_H
#define SERIALIZATIONOPERATORWITHDISTINCTPHENOTYPE_H
#include "SerializationOperator.h"


class SerializationOperatorWithDistinctPhenotype : public SerializationOperator {
public:
    virtual std::vector<std::string> serializePhenotype(Genotype* genotype) = 0;
    ~SerializationOperatorWithDistinctPhenotype() override = 0;
};



#endif //SERIALIZATIONOPERATORWITHDISTINCTPHENOTYPE_H
