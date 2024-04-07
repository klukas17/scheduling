//
// Created by mihael on 25/06/23.
//

#ifndef SCHEDULING_PREREQUISITE_H
#define SCHEDULING_PREREQUISITE_H

class Prerequisite {
    long job_id;
    long machine_id;
    long repetitions;
public:
    Prerequisite(long job_id, long machine_id, long repetitions);
    [[nodiscard]] long getJobId() const;
    [[nodiscard]] long getMachineId() const;
    [[nodiscard]] long getRepetitions() const;
};

#endif //SCHEDULING_PREREQUISITE_H

