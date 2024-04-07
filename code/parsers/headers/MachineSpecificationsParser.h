//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINESPECIFICATIONSPARSER_H
#define SCHEDULING_MACHINESPECIFICATIONSPARSER_H

#include <string>
#include "MachineTypeMap.h"

class MachineSpecificationsParser {
public:
    static MachineTypeMap* parse(const std::string& path);
};

#endif //SCHEDULING_MACHINESPECIFICATIONSPARSER_H
