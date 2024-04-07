//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_JOBEVENT_H
#define SCHEDULING_JOBEVENT_H

#include "Event.h"

class JobEvent : public virtual Event {
protected:
    long job_id;
public:
    JobEvent(double time, long job_id);
    ~JobEvent() override = 0;
    [[nodiscard]] long getJobId() const;
};

#endif //SCHEDULING_JOBEVENT_H
