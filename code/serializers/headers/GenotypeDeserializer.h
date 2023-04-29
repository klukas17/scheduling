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
    Topology* topology;
public:
    GenotypeDeserializer(Topology* topology);
    Individual* deserialize(std::string path);
};


#endif //SCHEDULING_GENOTYPEDESERIALIZER_H
