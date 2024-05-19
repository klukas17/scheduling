//
// Created by mihael on 4/10/24.
//

#ifndef SCHEDULERPARAMETERSGROUP_H
#define SCHEDULERPARAMETERSGROUP_H


class SchedulerParametersGroup {
public:
    double release_time;
    double due_time;
    double weight;
    double time;
    double remaining_processing_time_in_branch;
    int number_of_jobs_passed_through_a_machine;
    int number_of_jobs_in_branch;
    long free_spaces_in_buffer;
    bool prerequisites_satisfied;
    SchedulerParametersGroup(
        double release_time,
        double due_time,
        double weight,
        double time,
        double remaining_processing_time_in_branch,
        int number_of_jobs_passed_through_a_machine,
        int number_of_jobs_in_branch,
        long free_spaces_in_buffer,
        bool prerequisites_satisfied
    );
};



#endif //SCHEDULERPARAMETERSGROUP_H
