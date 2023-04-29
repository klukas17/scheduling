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
    YAML::Node jobs_node = doc["jobs"];

    if (jobs_node) {
        for (YAML::const_iterator it = jobs_node.begin(); it != jobs_node.end(); ++it) {
            const YAML::Node& job_node = (*it)["job"];
            long id = job_node["id"].as<long>();
            JobType* job_type = new JobType(id);
            job_type_map[id] = job_type;

            const YAML::Node& processing_times_node = job_node["processing_times"];
            if (processing_times_node) {
                for (YAML::const_iterator proc_it = processing_times_node.begin(); proc_it != processing_times_node.end(); proc_it++) {
                    const YAML::Node& processing_time_node = (*proc_it)["machine"];
                    long machine_id = processing_time_node["id"].as<long>();
                    long time = processing_time_node["time"].as<long>();
                    job_type->setProcessingTime(machine_id, time);
                }
            }
        }
    }

    else {
        // todo:error
        std::cerr << "Error: 'jobs' node not found in " << path << " file." << std::endl;
        exit(1);
    }

    return job_type_map;
}