//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOBTYPE_H
#define SCHEDULING_JOBTYPE_H

#include "map"
#include "set"

class JobType {
protected:
    long id;
    std::map<long, long> processing_times;
    std::set<long> job_families;
    std::set<long> forbidden_machine_types;
public:
    explicit JobType(long id);
    [[nodiscard]] long getId() const;
    std::map<long, long> getProcessingTimes();
    void setProcessingTime(long machine_id, long processing_time);
    std::set<long> getJobFamilies();
    void addJobFamily(long job_family_id);
    std::set<long> getForbiddenMachineTypes();
    void addForbiddenMachineType(long machine_type_id);
};


#endif //SCHEDULING_JOBTYPE_H
