//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "JobSequenceParser.h"
#include "yaml-cpp/yaml.h"

std::map<long, Job *> JobSequenceParser::parse(const std::string& path, std::map<long, JobType *> job_type_map) {

    std::map<long, Job*> jobs;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node job_sequence_node = doc["job_sequence"];

    if (job_sequence_node) {
        for (YAML::const_iterator it = job_sequence_node.begin(); it != job_sequence_node.end(); it++) {
            long id = (*it)["job_id"].as<long>();
            long job_type_id = (*it)["job_type_id"].as<long>();
            JobType* job_type = job_type_map[job_type_id];
            long release_time = ((*it)["release_time"]) ? (*it)["release_time"].as<long>() : 0;
            long due_time = ((*it)["due_time"]) ? (*it)["due_time"].as<long>() : release_time;
            long weight = ((*it)["weight"]) ? (*it)["weight"].as<long>() : 1;

            PathNode* paths_root_node = nullptr;
            const YAML::Node& processing_route_node = (*it)["processing_route"];
            if (processing_route_node) {
                if (processing_route_node.size() != 1) {
                    // todo:error
                    std::cerr << "Error: 'processing_route' node can have only one child in " << path << " file." << std::endl;
                    exit(1);
                }
                paths_root_node = parsePathNode(*processing_route_node.begin());
            }
            else {
                // todo:error
                std::cerr << "Error: 'processing_route' node not found in " << path << " file." << std::endl;
                exit(1);
            }

            Job* job = new Job(id, job_type, paths_root_node, release_time, due_time, weight);
            jobs[id] = job;
        }
    }

    else {
        // todo:error
        std::cerr << "Error: 'job_sequence' node not found in " << path << " file." << std::endl;
        exit(1);
    }

    return jobs;
}

PathNode *JobSequenceParser::parsePathNode(const YAML::Node &node) {
    long machine_id = node["machine_id"].as<long>();
    auto path_node = new PathNode(machine_id);

    const YAML::Node& sub_machines_node = node["sub_machines"];
    if (sub_machines_node) {
        for (YAML::const_iterator sub_machine_it = sub_machines_node.begin(); sub_machine_it != sub_machines_node.end(); sub_machine_it++) {
            path_node->addChild(parsePathNode(*sub_machine_it));
        }
    }

    const YAML::Node& prerequisites_node = node["prerequisites"];
    if (prerequisites_node) {
        for (YAML::const_iterator prerequisite_it = prerequisites_node.begin(); prerequisite_it != prerequisites_node.end(); prerequisite_it++) {
            long job_id = (*prerequisite_it)["job_id"].as<long>();
            long machine_id = (*prerequisite_it)["machine_id"].as<long>();
            long repetitions = (*prerequisite_it)["repetitions"] ? (*prerequisite_it)["repetitions"].as<long>() : 1;
            path_node->addPrerequisite(new Prerequisite(job_id, machine_id, repetitions));
        }
    }

    return path_node;
}