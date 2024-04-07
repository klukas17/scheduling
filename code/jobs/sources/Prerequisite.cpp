//
// Created by mihael on 25/06/23.
//

#include "Prerequisite.h"

Prerequisite::Prerequisite(long const job_id, long const machine_id, long const repetitions) {
    this->job_id = job_id;
    this->machine_id = machine_id;
    this->repetitions = repetitions;
}

long Prerequisite::getJobId() const {
    return job_id;
}

long Prerequisite::getMachineId() const {
    return machine_id;
}

long Prerequisite::getRepetitions() const {
    return repetitions;
}