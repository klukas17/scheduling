//
// Created by mihael on 29/04/23.
//

#include "JobSpecificationsParser.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

JobSpecificationsParser::JobSpecificationsParser() = default;

std::map<long, JobType *> JobSpecificationsParser::parse(const std::string& path) {

    std::map<long, JobType*> job_type_map;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node jobs_node = doc["jobs"];

    if (jobs_node) {
        for (YAML::const_iterator it = jobs_node.begin(); it != jobs_node.end(); ++it) {
            long id = (*it)["job_id"].as<long>();
            auto job_type = new JobType(id);
            job_type_map[id] = job_type;

            const YAML::Node& processing_times_node = (*it)["processing_times"];
            if (processing_times_node) {
                for (YAML::const_iterator proc_it = processing_times_node.begin(); proc_it != processing_times_node.end(); proc_it++) {
                    long machine_id = (*proc_it)["machine_id"].as<long>();
                    long time = (*proc_it)["time"].as<long>();
                    job_type->setProcessingTime(machine_id, time);
                }
            }

            const YAML::Node& job_families_node = (*it)["job_families"];
            if (job_families_node) {
                for (YAML::const_iterator job_family_id = job_families_node.begin(); job_family_id != job_families_node.end(); job_family_id++) {
                    job_type->addJobFamily((*job_family_id).as<long>());
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