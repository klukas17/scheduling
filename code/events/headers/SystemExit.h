//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SYSTEMEXIT_H
#define SCHEDULING_SYSTEMEXIT_H

#include "JobEvent.h"

class SystemExit final : public JobEvent {
public:
    SystemExit(double time, long job_id);
};

#endif //SCHEDULING_SYSTEMEXIT_H
