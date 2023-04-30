//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPESERIALIZER_H
#define SCHEDULING_GENOTYPESERIALIZER_H

#include "string"
#include "Individual.h"
#include <yaml-cpp/yaml.h>

class GenotypeSerializer {
public:
    GenotypeSerializer();
    static void serialize(const std::string& path, Individual* individual);
    static void serializeNode(GenotypeNode* node, YAML::Emitter& out);
};


#endif //SCHEDULING_GENOTYPESERIALIZER_H
