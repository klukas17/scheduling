//
// Created by mihael on 9/2/23.
//

/**
 * @file PrerequisitesWaitStart.h
 * @brief Defines the PrerequisitesWaitStart class for representing events when a job starts waiting for prerequisites.
 */

#ifndef SCHEDULING_PREREQUISITESWAITSTART_H
#define SCHEDULING_PREREQUISITESWAITSTART_H

#include "JobAndMachineEvent.h"

/**
 * @class PrerequisitesWaitStart
 * @brief Represents an event when a job starts waiting for prerequisites.
 *
 * The PrerequisitesWaitStart class is a derived class of JobAndMachineEvent and is used to represent an event
 * when a job starts waiting for its prerequisites to be completed before it can proceed to execution.
 */
class PrerequisitesWaitStart : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a PrerequisitesWaitStart object with the specified parameters.
     * @param time The time at which this event occurs.
     * @param job_id The identifier of the job waiting for prerequisites.
     * @param machine_id The identifier of the machine on which the job will execute.
     * @param step_id The identifier of the processing step associated with the job.
     */
    PrerequisitesWaitStart(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_PREREQUISITESWAITSTART_H
