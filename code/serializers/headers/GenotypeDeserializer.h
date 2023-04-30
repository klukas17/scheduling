//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPEDESERIALIZER_H
#define SCHEDULING_GENOTYPEDESERIALIZER_H

#include "Topology.h"
#include "Individual.h"
#include "string"

class GenotypeDeserializer {
private:
public:
    explicit GenotypeDeserializer();
    static Individual* deserialize(const std::string& path, Topology* topology);
};


#endif //SCHEDULING_GENOTYPEDESERIALIZER_H
