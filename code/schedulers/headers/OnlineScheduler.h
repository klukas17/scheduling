//
// Created by mihael on 4/23/24.
//

#ifndef ONLINESCHEDULER_H
#define ONLINESCHEDULER_H

#include "SchedulerParametersGroup.h"
#include "SchedulerParametersMachine.h"


class OnlineScheduler {
public:
    // virtual double calculateResultForGroup(SchedulerParametersGroup* params) = 0;
    // virtual double calculateResultForMachine(SchedulerParametersMachine* params) = 0;
    virtual ~OnlineScheduler();
};



#endif //ONLINESCHEDULER_H
