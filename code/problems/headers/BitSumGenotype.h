//
// Created by mihael on 2/18/24.
//

#ifndef BITSUMGENOTYPE_H
#define BITSUMGENOTYPE_H
#include "Genotype.h"
#include "vector"


class BitSumGenotype : public Genotype {
public:
    std::vector<int> bits;
    BitSumGenotype(std::vector<int>& bits);
};



#endif //BITSUMGENOTYPE_H
