//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOBSPECIFICATIONSPARSER_H
#define SCHEDULING_JOBSPECIFICATIONSPARSER_H

#include "string"
#include "map"
#include "JobType.h"

class JobSpecificationsParser {
public:
    JobSpecificationsParser();
    std::map<long, JobType*> parse(std::string path);
};


#endif //SCHEDULING_JOBSPECIFICATIONSPARSER_H