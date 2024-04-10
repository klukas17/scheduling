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
    double number_of_jobs_passed_through_a_child_machine;
    SchedulerParametersGroup(
        double release_time,
        double due_time,
        double weight,
        double time,
        double number_of_jobs_passed_through_a_child_machine
    );
};



#endif //SCHEDULERPARAMETERSGROUP_H
