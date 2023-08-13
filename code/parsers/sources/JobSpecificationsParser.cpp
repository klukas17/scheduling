//
// Created by mihael on 29/04/23.
//

/**
 * @file JobSpecificationsParser.cpp
 * @brief Implements the member functions of the JobSpecificationsParser class.
 */


#include "JobSpecificationsParser.h"
#include "SchedulingError.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

JobTypeMap* JobSpecificationsParser::parse(const std::string& path) {

    auto job_type_map = new JobTypeMap();

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node jobs_node = doc["jobs"];

    if (jobs_node) {
        for (YAML::const_iterator it = jobs_node.begin(); it != jobs_node.end(); ++it) {
            if (!(*it)["job_id"]) {
                throw SchedulingError("Entry in the 'jobs' array must contain 'job_id' field in the file " + path);
            }
            long id = (*it)["job_id"].as<long>();
            auto job_type = new JobType(id);
            job_type_map->addJobType(id, job_type);

            const YAML::Node& processing_times_node = (*it)["processing_times"];
            if (processing_times_node) {
                for (YAML::const_iterator proc_it = processing_times_node.begin(); proc_it != processing_times_node.end(); proc_it++) {
                    if (!(*proc_it)["machine_id"]) {
                        throw SchedulingError("Entry in the 'processing_times' array must contain 'machine_id' field in the file " + path);
                    }
                    long machine_id = (*proc_it)["machine_id"].as<long>();
                    if (!(*proc_it)["time"]) {
                        throw SchedulingError("Entry in the 'processing_times' array must contain 'time' field in the file " + path);
                    }
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

            const YAML::Node& forbidden_machine_types_node = (*it)["forbidden_machine_types"];
            if (forbidden_machine_types_node) {
                for (YAML::const_iterator machine_type_id = forbidden_machine_types_node.begin(); machine_type_id != forbidden_machine_types_node.end(); machine_type_id++) {
                    job_type->addForbiddenMachineType((*machine_type_id).as<long>());
                }
            }
        }
    } else {
        throw SchedulingError("'jobs' key not found in the file " + path);
    }

    return job_type_map;
}