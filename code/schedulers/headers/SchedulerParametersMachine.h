//
// Created by mihael on 4/10/24.
//

#ifndef SCHEDULERPARAMETERSMACHINE_H
#define SCHEDULERPARAMETERSMACHINE_H


class SchedulerParametersMachine {
    double release_time;
    double due_time;
    double weight;
    bool batch_processing_enabled;
    int number_of_sibling_jobs_in_buffer;
    SchedulerParametersMachine(
        double release_time,
        double due_time,
        double weight,
        bool batch_processing_enabled,
        int number_of_sibling_jobs_in_buffer
    );
};



#endif //SCHEDULERPARAMETERSMACHINE_H
