//
// Created by mihael on 2/16/24.
//

#ifndef INITIALIZEROPERATOR_H
#define INITIALIZEROPERATOR_H
#include "Genotype.h"


class CreationOperator {
public:
    virtual Genotype* create() = 0;
    virtual ~CreationOperator() = 0;
};



#endif //INITIALIZEROPERATOR_H
