//
// Created by mihael on 2/16/24.
//

#ifndef GENOTYPE_H
#define GENOTYPE_H

class Genotype {
public:
    virtual ~Genotype() = 0;
    virtual Genotype* copy() = 0;
};



#endif //GENOTYPE_H
