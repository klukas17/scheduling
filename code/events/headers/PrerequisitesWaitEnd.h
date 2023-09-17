//
// Created by mihael on 9/2/23.
//

/**
 * @file PrerequisitesWaitEnd.h
 * @brief Defines the PrerequisitesWaitEnd class for representing events when a job ends waiting for prerequisites.
 */

#ifndef SCHEDULING_PREREQUISITESWAITEND_H
#define SCHEDULING_PREREQUISITESWAITEND_H

#include "JobAndMachineEvent.h"

/**
 * @class PrerequisitesWaitEnd
 * @brief Represents an event when prerequisites for a job are completed.
 *
 * The PrerequisitesWaitEnd class is a derived class of JobAndMachineEvent and is used to represent an event
 * when the prerequisites for a job are completed, allowing the job to proceed to its execution.
 */
class PrerequisitesWaitEnd : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a PrerequisitesWaitEnd object with the specified parameters.
     * @param time The time at which this event occurs.
     * @param job_id The identifier of the job waiting for prerequisites.
     * @param machine_id The identifier of the machine on which the job will execute.
     * @param step_id The identifier of the processing step associated with the job.
     */
    PrerequisitesWaitEnd(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_PREREQUISITESWAITEND_H

