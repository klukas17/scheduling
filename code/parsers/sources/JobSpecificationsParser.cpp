//
// Created by mihael on 29/04/23.
//

#include "JobSpecificationsParser.h"
#include "SchedulingError.h"
#include "yaml-cpp/yaml.h"

JobTypeMap* JobSpecificationsParser::parse(const std::string& path) {

    auto const job_type_map = new JobTypeMap();

    YAML::Node doc = YAML::LoadFile(path);

    if (YAML::Node jobs_node = doc["jobs"]; jobs_node) {
        for (YAML::const_iterator it = jobs_node.begin(); it != jobs_node.end(); ++it) {
            if (!(*it)["job_id"]) {
                throw SchedulingError("Entry in the 'jobs' array must contain 'job_id' field in the file " + path);
            }
            long const id = (*it)["job_id"].as<long>();
            long const preempt = (*it)["preempt"] && (*it)["preempt"].as<bool>();
            auto const job_type = new JobType(id, preempt);
            job_type_map->addJobType(id, job_type);

            if (YAML::Node processing_times_node = (*it)["processing_times"]; processing_times_node) {
                for (auto proc_it = processing_times_node.begin(); proc_it != processing_times_node.end(); ++proc_it) {
                    if (!(*proc_it)["machine_id"]) {
                        throw SchedulingError("Entry in the 'processing_times' array must contain 'machine_id' field in the file " + path);
                    }
                    long const machine_id = (*proc_it)["machine_id"].as<long>();
                    if (!(*proc_it)["time"]) {
                        throw SchedulingError("Entry in the 'processing_times' array must contain 'time' field in the file " + path);
                    }
                    auto const time = (*proc_it)["time"].as<double>();
                    job_type->setProcessingTime(machine_id, time);
                }
            }

            if (YAML::Node forbidden_machine_types_node = (*it)["forbidden_machine_types"]; forbidden_machine_types_node) {
                for (auto machine_type_id = forbidden_machine_types_node.begin(); machine_type_id != forbidden_machine_types_node.end(); ++machine_type_id) {
                    job_type->addForbiddenMachineType(machine_type_id->as<long>());
                }
            }
        }
    } else {
        throw SchedulingError("'jobs' key not found in the file " + path);
    }

    return job_type_map;
}