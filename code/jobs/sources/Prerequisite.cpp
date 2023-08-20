//
// Created by mihael on 25/06/23.
//

/**
 * @file Prerequisite.cpp
 * @brief Implements the member functions of the Prerequisite class.
 */

#include "Prerequisite.h"

Prerequisite::Prerequisite(long job_id, long machine_id, long repetitions) {
    this->job_id = job_id;
    this->machine_id = machine_id;
    this->repetitions = repetitions;
}

long Prerequisite::getJobId() {
    return job_id;
}

long Prerequisite::getMachineId() {
    return machine_id;
}

long Prerequisite::getRepetitions() {
    return repetitions;
}