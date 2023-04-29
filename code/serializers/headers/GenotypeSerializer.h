//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPESERIALIZER_H
#define SCHEDULING_GENOTYPESERIALIZER_H

#include "string"
#include "Individual.h"

class GenotypeSerializer {
public:
    GenotypeSerializer();
    void serialize(std::string path, Individual* individual);
};


#endif //SCHEDULING_GENOTYPESERIALIZER_H
