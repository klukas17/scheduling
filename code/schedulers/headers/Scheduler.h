//
// Created by mihael on 4/10/24.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "SchedulerParametersGroup.h"
#include "SchedulerParametersMachine.h"

class Scheduler {
public:
    virtual double calculateResultForGroup(SchedulerParametersGroup* params) = 0;
    virtual double calculateResultForMachine(SchedulerParametersMachine* params) = 0;
    virtual ~Scheduler();
};



#endif //SCHEDULER_H
