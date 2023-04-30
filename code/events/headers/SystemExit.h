//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SYSTEMEXIT_H
#define SCHEDULING_SYSTEMEXIT_H

#include "JobEvent.h"

class SystemExit : public JobEvent {
public:
    SystemExit(long time, long job_id);
};


#endif //SCHEDULING_SYSTEMEXIT_H
