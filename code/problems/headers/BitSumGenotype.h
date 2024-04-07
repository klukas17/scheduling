//
// Created by mihael on 2/18/24.
//

#ifndef BITSUMGENOTYPE_H
#define BITSUMGENOTYPE_H

#include "Genotype.h"
#include "vector"

class BitSumGenotype final : public Genotype {
public:
    std::vector<int> bits;
    explicit BitSumGenotype(std::vector<int>& bits);
};



#endif //BITSUMGENOTYPE_H
