//
// Created by mihael on 29/04/23.
//

#include "MachineSpecificationsParser.h"
#include "SchedulingError.h"
#include <yaml-cpp/yaml.h>
#include <climits>

MachineTypeMap* MachineSpecificationsParser::parse(const std::string& path) {
    auto machine_type_map = new MachineTypeMap();

    YAML::Node doc = YAML::LoadFile(path);

    if (YAML::Node machines_node = doc["machines"]; machines_node) {
        for (YAML::const_iterator it = machines_node.begin(); it != machines_node.end(); ++it) {
            std::vector<std::tuple<double, long, long>> machine_type_setup_data;
            std::vector<std::tuple<long, long>> machine_type_batch_data;
            if (!(*it)["machine_id"]) {
                throw SchedulingError("Entry in the 'machines' array must contain 'machine_id' field in the file " + path);
            }
            long id = (*it)["machine_id"].as<long>();
            long preempt = (*it)["preempt"] && (*it)["preempt"].as<bool>();
            YAML::Node setup_node = (*it)["setup"];
            for (auto setup_it = setup_node.begin(); setup_it != setup_node.end(); ++setup_it) {
                if (!(*setup_it)["time"]) {
                    throw SchedulingError("Entry in the 'setup' array must contain 'time' field in the file " + path);
                }
                auto time = (*setup_it)["time"].as<double>();
                long from = (*setup_it)["from"] ? (*setup_it)["from"].as<long>() : -1;
                long to = (*setup_it)["to"] ? (*setup_it)["to"].as<long>() : -1;
                machine_type_setup_data.emplace_back(time, from, to);
            }
            YAML::Node batch_processing_node = (*it)["batch_processing"];
            for (auto batch_it = batch_processing_node.begin(); batch_it != batch_processing_node.end(); ++batch_it) {
                if (!(*batch_it)["job_type_id"]) {
                    throw SchedulingError("Entry in the 'batch_processing' array must contain 'job_type_id' field in the file " + path);
                }
                long job_type_id = (*batch_it)["job_type_id"].as<long>();
                long jobs_per_batch = (*batch_it)["jobs_per_batch"] ? (*batch_it)["jobs_per_batch"].as<long>() : LONG_MAX;
                machine_type_batch_data.emplace_back(job_type_id, jobs_per_batch);
            }
            auto machine_type = new MachineType(id, preempt, machine_type_setup_data, machine_type_batch_data);
            machine_type_map->addMachineType(id, machine_type);
        }
    } else {
        throw SchedulingError("'machines' key not found in the file " + path);
    }

    return machine_type_map;
}
