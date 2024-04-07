//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SYSTEMENTRY_H
#define SCHEDULING_SYSTEMENTRY_H

#include "JobEvent.h"

class SystemEntry final : public JobEvent {
public:
    SystemEntry(double time, long job_id);
};

#endif //SCHEDULING_SYSTEMENTRY_H
