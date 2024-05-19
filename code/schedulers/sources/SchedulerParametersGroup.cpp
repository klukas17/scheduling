//
// Created by mihael on 4/10/24.
//

#include "SchedulerParametersGroup.h"

SchedulerParametersGroup::SchedulerParametersGroup(
    double release_time,
    double due_time,
    double weight,
    double time,
    double remaining_processing_time_in_branch,
    int number_of_jobs_passed_through_a_machine,
    int number_of_jobs_in_branch,
    long free_spaces_in_buffer,
    bool prerequisites_satisfied
) {
    this->release_time = release_time;
    this->due_time = due_time;
    this->weight = weight;
    this->time = time;
    this->remaining_processing_time_in_branch = remaining_processing_time_in_branch;
    this->number_of_jobs_passed_through_a_machine = number_of_jobs_passed_through_a_machine;
    this->number_of_jobs_in_branch = number_of_jobs_in_branch;
    this->free_spaces_in_buffer = free_spaces_in_buffer;
    this->prerequisites_satisfied = prerequisites_satisfied;
}
