//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SYSTEMENTRY_H
#define SCHEDULING_SYSTEMENTRY_H

#include "JobEvent.h"

class SystemEntry : public JobEvent {
public:
    SystemEntry(long time, long job_id);
};


#endif //SCHEDULING_SYSTEMENTRY_H
