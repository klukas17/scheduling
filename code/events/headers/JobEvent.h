//
// Created by mihael on 30/04/23.
//

/**
 * @file JobEvent.h
 * @brief Defines the JobEvent class for representing a job-related event in the scheduling simulation.
 */

#ifndef SCHEDULING_JOBEVENT_H
#define SCHEDULING_JOBEVENT_H

#include "Event.h"

/**
 * @class JobEvent
 * @brief Represents a job-related event in the scheduling simulation.
 *
 * The JobEvent class is derived from the Event class and represents an event that is related to a specific job
 * in the scheduling simulation process. It includes attributes to store the associated job's identifier.
 */
class JobEvent : public virtual Event {
protected:
    long job_id; /**< Identifier of the job associated with the event. */
public:
    /**
     * @brief Constructs a JobEvent object with the provided time and job identifier.
     * @param time The time at which the job-related event occurs.
     * @param job_id The identifier of the job associated with the event.
     */
    JobEvent(long time, long job_id);

    /**
     * @brief Virtual destructor for the JobEvent class.
     */
    ~JobEvent() override = 0;

    /**
     * @brief Retrieves the identifier of the job associated with the event.
     * @return The identifier of the associated job.
     */
    [[nodiscard]] long getJobId() const;
};

#endif //SCHEDULING_JOBEVENT_H
