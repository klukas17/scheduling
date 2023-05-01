//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOBSEQUENCEPARSER_H
#define SCHEDULING_JOBSEQUENCEPARSER_H

#include "string"
#include "map"
#include "JobType.h"
#include "Job.h"
#include "yaml-cpp/yaml.h"

class JobSequenceParser {
public:
    JobSequenceParser();
    static std::map<long, Job*> parse(const std::string& path, std::map<long, JobType*> job_type_map);
    static void parseMachineList(const YAML::Node& node, Job* job);
};


#endif //SCHEDULING_JOBSEQUENCEPARSER_H
