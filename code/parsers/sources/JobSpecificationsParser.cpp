//
// Created by mihael on 29/04/23.
//

#include "JobSpecificationsParser.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

JobSpecificationsParser::JobSpecificationsParser() {}

std::map<long, JobType *> JobSpecificationsParser::parse(std::string path) {

    std::map<long, JobType*> job_type_map;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node jobsNode = doc["jobs"];

    if (jobsNode) {
        for (YAML::const_iterator it = jobsNode.begin(); it != jobsNode.end(); ++it) {
            const YAML::Node& job_node = (*it)["job"];
            long id = job_node["id"].as<long>();
            JobType* job_type = new JobType(id);
            job_type_map[id] = job_type;
        }
    }

    else {
        // todo:error
        std::cerr << "Error: 'jobs' node not found in " << path << " file." << std::endl;
        exit(1);
    }

    return job_type_map;
}