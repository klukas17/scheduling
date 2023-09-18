//
// Created by mihael on 9/18/23.
//

/**
 * @file SystemExitForced.h
 * @brief Defines the SystemExitForced class for representing a forced system exit event in the scheduling simulation.
 */

#ifndef SCHEDULING_SYSTEMEXITFORCED_H
#define SCHEDULING_SYSTEMEXITFORCED_H

#include "JobEvent.h"

/**
 * @class SystemExitForced
 * @brief Represents a forced system exit event in the scheduling simulation.
 *
 * The SystemExitForced class is derived from the JobEvent class and represents an event that signifies the forced exit of a job
 * from the scheduling system. It includes attributes to store the time of the event and the associated job's identifier.
 */
class SystemExitForced : public JobEvent {
public:
    /**
     * @brief Constructs a SystemExitForced object with the provided time and job identifier.
     * @param time The time at which the system exit event occurs.
     * @param job_id The identifier of the job associated with the event.
     */
    SystemExitForced(long time, long job_id);
};


#endif //SCHEDULING_SYSTEMEXITFORCED_H
