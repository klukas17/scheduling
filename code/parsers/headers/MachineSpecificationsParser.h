//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINESPECIFICATIONSPARSER_H
#define SCHEDULING_MACHINESPECIFICATIONSPARSER_H

#include "string"
#include "map"
#include "MachineType.h"

class MachineSpecificationsParser {
public:
    MachineSpecificationsParser();
    static std::map<long, MachineType*> parse(const std::string& path);
};


#endif //SCHEDULING_MACHINESPECIFICATIONSPARSER_H
