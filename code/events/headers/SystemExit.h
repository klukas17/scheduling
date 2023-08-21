//
// Created by mihael on 29/04/23.
//

/**
 * @file SystemExit.h
 * @brief Defines the SystemExit class for representing a system exit event in the scheduling simulation.
 */

#ifndef SCHEDULING_SYSTEMEXIT_H
#define SCHEDULING_SYSTEMEXIT_H

#include "JobEvent.h"

/**
 * @class SystemExit
 * @brief Represents a system exit event in the scheduling simulation.
 *
 * The SystemExit class is derived from the JobEvent class and represents an event that signifies the exit of a job
 * from the scheduling system. It includes attributes to store the time of the event and the associated job's identifier.
 */
class SystemExit : public JobEvent {
public:
    /**
     * @brief Constructs a SystemExit object with the provided time and job identifier.
     * @param time The time at which the system exit event occurs.
     * @param job_id The identifier of the job associated with the event.
     */
    SystemExit(long time, long job_id);
};

#endif //SCHEDULING_SYSTEMEXIT_H
