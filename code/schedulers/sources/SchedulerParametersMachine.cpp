//
// Created by mihael on 4/10/24.
//

#include "SchedulerParametersMachine.h"

SchedulerParametersMachine::SchedulerParametersMachine(
    double release_time,
    double due_time,
    double weight,
    double time,
    double combined_weights_of_batch_compatible_jobs,
    int number_of_batch_compatible_jobs
) {
    this->release_time = release_time;
    this->due_time = due_time;
    this->weight = weight;
    this->time = time;
    this->combined_weights_of_batch_compatible_jobs = combined_weights_of_batch_compatible_jobs;
    this->number_of_batch_compatible_jobs = number_of_batch_compatible_jobs;
}
