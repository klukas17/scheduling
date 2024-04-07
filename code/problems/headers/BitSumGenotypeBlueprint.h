//
// Created by mihael on 2/18/24.
//

#ifndef BITSUMGENOTYPEBLUEPRINT_H
#define BITSUMGENOTYPEBLUEPRINT_H

#include "GenotypeBlueprint.h"

class BitSumGenotypeBlueprint final : public GenotypeBlueprint {
public:
    int number_of_bits;
    explicit BitSumGenotypeBlueprint(int number_of_bits);
};



#endif //BITSUMGENOTYPEBLUEPRINT_H
