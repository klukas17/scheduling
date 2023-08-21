//
// Created by mihael on 29/04/23.
//

/**
 * @file SystemEntry.h
 * @brief Defines the SystemEntry class for representing a system entry event in the scheduling simulation.
 */

#ifndef SCHEDULING_SYSTEMENTRY_H
#define SCHEDULING_SYSTEMENTRY_H

#include "JobEvent.h"

/**
 * @class SystemEntry
 * @brief Represents a system entry event in the scheduling simulation.
 *
 * The SystemEntry class is derived from the JobEvent class and represents an event that signifies the entry of a job
 * into the scheduling system. It includes attributes to store the time of the event and the associated job's identifier.
 */
class SystemEntry : public JobEvent {
public:
    /**
     * @brief Constructs a SystemEntry object with the provided time and job identifier.
     * @param time The time at which the system entry event occurs.
     * @param job_id The identifier of the job associated with the event.
     */
    SystemEntry(long time, long job_id);
};

#endif //SCHEDULING_SYSTEMENTRY_H
