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
    bool buffer_has_free_space;
    bool prerequisites_satisfied;
    SchedulerParametersGroup(
        double release_time,
        double due_time,
        double weight,
        double time,
        double remaining_processing_time_in_branch,
        int number_of_jobs_passed_through_a_machine,
        int number_of_jobs_in_branch,
        bool buffer_has_free_space,
        bool prerequisites_satisfied
    );
};



#endif //SCHEDULERPARAMETERSGROUP_H
