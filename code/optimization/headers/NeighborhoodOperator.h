//
// Created by mihael on 2/16/24.
//

#ifndef NEIGHBORHOODOPERATOR_H
#define NEIGHBORHOODOPERATOR_H
#include <vector>

#include "Genotype.h"


class NeighborhoodOperator {
public:
    virtual std::vector<Genotype*> createNeighborhood(Genotype* genotype) = 0;
    virtual ~NeighborhoodOperator() = 0;
};



#endif //NEIGHBORHOODOPERATOR_H
