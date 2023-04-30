//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SYSTEMEXIT_H
#define SCHEDULING_SYSTEMEXIT_H

#include "Event.h"

class SystemExit : public Event {
private:
    long job_id;
public:
    SystemExit(long time, long job_id);
    [[nodiscard]] long getJobId() const;
};


#endif //SCHEDULING_SYSTEMEXIT_H
