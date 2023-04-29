//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINETOPOLOGYPARSER_H
#define SCHEDULING_MACHINETOPOLOGYPARSER_H

#include "Topology.h"
#include "string"
#include "map"
#include "MachineType.h"

class MachineTopologyParser {
public:
    MachineTopologyParser();
    Topology* parse(std::string path, std::map<long, MachineType*> machine_type_map);
};


#endif //SCHEDULING_MACHINETOPOLOGYPARSER_H
