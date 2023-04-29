//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "JobSequenceParser.h"
#include "yaml-cpp/yaml.h"

JobSequenceParser::JobSequenceParser() {}

std::vector<Job *> JobSequenceParser::parse(std::string path, std::map<long, JobType *> job_type_map) {

    std::vector<Job*> jobs;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node job_sequence_node = doc["job_sequence"];

    if (job_sequence_node) {
        for (YAML::const_iterator it = job_sequence_node.begin(); it != job_sequence_node.end(); it++) {
            const YAML::Node& job_node = (*it)["job"];
            long id = job_node["id"].as<long>();
            long job_type_id = job_node["job_type_id"].as<long>();
            Job* job = new Job(id, job_type_map[job_type_id]);
            jobs.push_back(job);
        }
    }

    else {
        // todo:error
        std::cerr << "Error: 'job_sequence' node not found in " << path << " file." << std::endl;
        exit(1);
    }

    return jobs;
}