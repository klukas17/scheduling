//
// Created by mihael on 4/10/24.
//

#include "SchedulerParametersMachine.h"

SchedulerParametersMachine::SchedulerParametersMachine(
    double const release_time,
    double const due_time,
    double const weight,
    bool const batch_processing_enabled,
    int const number_of_sibling_jobs_in_buffer
) {
    this->release_time = release_time;
    this->due_time = due_time;
    this->weight = weight;
    this->batch_processing_enabled = batch_processing_enabled;
    this->number_of_sibling_jobs_in_buffer = number_of_sibling_jobs_in_buffer;
}
