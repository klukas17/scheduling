//
// Created by mihael on 4/10/24.
//

#include "SchedulerParametersGroup.h"

SchedulerParametersGroup::SchedulerParametersGroup(
    double const release_time,
    double const due_time,
    double const weight,
    double const time,
    double const number_of_jobs_passed_through_a_child_machine
) {
    this->release_time = release_time;
    this->due_time = due_time;
    this->weight = weight;
    this->time = time;
    this->number_of_jobs_passed_through_a_child_machine = number_of_jobs_passed_through_a_child_machine;
}
