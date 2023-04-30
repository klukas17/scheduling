//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOBSEQUENCEPARSER_H
#define SCHEDULING_JOBSEQUENCEPARSER_H

#include "string"
#include "map"
#include "JobType.h"
#include "Job.h"

class JobSequenceParser {
public:
    JobSequenceParser();
    static std::map<long, Job*> parse(const std::string& path, std::map<long, JobType*> job_type_map);
};


#endif //SCHEDULING_JOBSEQUENCEPARSER_H
