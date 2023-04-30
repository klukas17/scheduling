//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SYSTEMENTRY_H
#define SCHEDULING_SYSTEMENTRY_H

#include "Event.h"

class SystemEntry : public Event {
private:
    long job_id;
public:
    SystemEntry(long time, long job_id);
    [[nodiscard]] long getJobId() const;
};


#endif //SCHEDULING_SYSTEMENTRY_H
