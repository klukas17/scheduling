//
// Created by mihael on 8/13/23.
//

#include "JobTypeMap.h"
#include "SchedulingError.h"

JobTypeMap::JobTypeMap() = default;

std::map<long, JobType *> JobTypeMap::getJobTypeMap() {
    return job_type_map;
}

JobType* JobTypeMap::getJobType(long const job_type_id) {
    if (!job_type_map.contains(job_type_id)) {
        return nullptr;
    }
    return job_type_map[job_type_id];
}

void JobTypeMap::addJobType(long const job_type_id, JobType *job_type) {
    if (job_type_map.contains(job_type_id)) {
        throw SchedulingError("JobType of id " + std::to_string(job_type_id) + " already exists in JobTypeMap.");
    }
    job_type_map[job_type_id] = job_type;
}