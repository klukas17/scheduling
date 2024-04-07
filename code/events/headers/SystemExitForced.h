//
// Created by mihael on 9/18/23.
//

#ifndef SCHEDULING_SYSTEMEXITFORCED_H
#define SCHEDULING_SYSTEMEXITFORCED_H

#include "JobEvent.h"

class SystemExitForced final : public JobEvent {
public:
    SystemExitForced(double time, long job_id);
};


#endif //SCHEDULING_SYSTEMEXITFORCED_H
