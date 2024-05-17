//
// Created by mihael on 4/10/24.
//

#ifndef SCHEDULERPARAMETERSMACHINE_H
#define SCHEDULERPARAMETERSMACHINE_H


class SchedulerParametersMachine {
public:
    double release_time;
    double due_time;
    double weight;
    double time;
    double combined_weights_of_batch_compatible_jobs;
    int number_of_batch_compatible_jobs;
    SchedulerParametersMachine(
        double release_time,
        double due_time,
        double weight,
        double time,
        double combined_weights_of_batch_compatible_jobs,
        int number_of_batch_compatible_jobs
    );
};



#endif //SCHEDULERPARAMETERSMACHINE_H
