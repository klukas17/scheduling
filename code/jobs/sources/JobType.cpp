//
// Created by mihael on 29/04/23.
//

#include "JobType.h"

JobType::JobType(long id) {
    this->id = id;
}

long JobType::getId() const {
    return id;
}

std::map<long, long> JobType::getProcessingTimes() {
    return processing_times;
}

void JobType::setProcessingTime(long machine_id, long processing_time) {
    processing_times[machine_id] = processing_time;
}

std::set<long> JobType::getJobFamilies() {
    return job_families;
}

void JobType::addJobFamily(long job_family_id) {
    job_families.insert(job_family_id);
}