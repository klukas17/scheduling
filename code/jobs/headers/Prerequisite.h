//
// Created by mihael on 25/06/23.
//

#ifndef SCHEDULING_PREREQUISITE_H
#define SCHEDULING_PREREQUISITE_H


class Prerequisite {
private:
    long job_id;
    long machine_id;
    long repetitions;
public:
    Prerequisite(long job_id, long machine_id, long repetitions);
    long getJobId();
    long getMachineId();
    long getRepetitions();
};


#endif //SCHEDULING_PREREQUISITE_H
