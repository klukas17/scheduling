//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "JobSequenceParser.h"
#include "yaml-cpp/yaml.h"

JobSequenceParser::JobSequenceParser() = default;

std::map<long, Job *> JobSequenceParser::parse(const std::string& path, std::map<long, JobType *> job_type_map) {

    std::map<long, Job*> jobs;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node job_sequence_node = doc["job_sequence"];

    if (job_sequence_node) {
        for (YAML::const_iterator it = job_sequence_node.begin(); it != job_sequence_node.end(); it++) {
            long id = (*it)["job_id"].as<long>();
            long job_type_id = (*it)["job_type_id"].as<long>();
            JobType* job_type = job_type_map[job_type_id];
            long release_date = ((*it)["release_date"]) ? (*it)["release_date"].as<long>() : 0;
            long due_date = ((*it)["due_date"]) ? (*it)["due_date"].as<long>() : release_date;
            long weight = ((*it)["weight"]) ? (*it)["weight"].as<long>() : 1;
            Job* job = new Job(id, job_type, release_date, due_date, weight);
            jobs[id] = job;

            std::map<long, long> job_type_processing_times = job_type->getProcessingTimes();
            for (auto & job_type_processing_time : job_type_processing_times) {
                job->setProcessingTime(job_type_processing_time.first, job_type_processing_time.second);
            }

            const YAML::Node& processing_route_node = (*it)["processing_route"];
            if (processing_route_node) {
                for (YAML::const_iterator proc_it = processing_route_node.begin(); proc_it != processing_route_node.end(); proc_it++) {
                    parseMachineList(*proc_it, job);
                }
            }
            else {
                // todo:error
                std::cerr << "Error: 'processing_route' node not found in " << path << " file." << std::endl;
                exit(1);
            }
        }
    }

    else {
        // todo:error
        std::cerr << "Error: 'job_sequence' node not found in " << path << " file." << std::endl;
        exit(1);
    }

    return jobs;
}

void JobSequenceParser::parseMachineList(const YAML::Node& node, Job *job) {
    long machine_id = node["machine_id"].as<long>();
    job->addMachineToProcessingRoute(machine_id);

    const YAML::Node& sub_machines_node = node["sub_machines"];
    if (sub_machines_node) {
        for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
            parseMachineList(*sub_machine_it, job);
        }
    }
}