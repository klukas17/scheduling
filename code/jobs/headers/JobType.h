//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOBTYPE_H
#define SCHEDULING_JOBTYPE_H

#include "map"

class JobType {
protected:
    long id;
    std::map<long, long> processing_times;
public:
    explicit JobType(long id);
    [[nodiscard]] long getId() const;
    std::map<long, long> getProcessingTimes();
    void setProcessingTime(long machine_id, long processing_time);
};


#endif //SCHEDULING_JOBTYPE_H
