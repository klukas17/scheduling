//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOBSPECIFICATIONSPARSER_H
#define SCHEDULING_JOBSPECIFICATIONSPARSER_H

#include <string>
#include "JobTypeMap.h"

class JobSpecificationsParser {
public:
    static JobTypeMap* parse(const std::string& path);
};

#endif //SCHEDULING_JOBSPECIFICATIONSPARSER_H

