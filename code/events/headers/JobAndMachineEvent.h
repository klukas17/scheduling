//
// Created by mihael on 8/21/23.
//

/**
 * @file JobAndMachineEvent.h
 * @brief Defines the JobAndMachineEvent class for representing an event related to both a job and a machine in the scheduling simulation.
 */

#ifndef SCHEDULING_JOBANDMACHINEEVENT_H
#define SCHEDULING_JOBANDMACHINEEVENT_H

#include "Event.h"
#include "MachineEvent.h"
#include "JobEvent.h"

/**
 * @class JobAndMachineEvent
 * @brief Represents an event related to both a job and a machine in the scheduling simulation.
 *
 * The JobAndMachineEvent class is derived from both the JobEvent and MachineEvent classes, representing an event that is
 * related to both a specific job and a specific machine in the scheduling simulation process. It includes attributes to
 * store the associated step identifier.
 */
class JobAndMachineEvent : public JobEvent, public MachineEvent {
private:
    long step_id; /**< Identifier of the step associated with the event. */
public:
    /**
     * @brief Constructs a JobAndMachineEvent object with the provided time, job identifier, machine identifier, and step identifier.
     * @param time The time at which the event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine associated with the event.
     * @param step_id The identifier of the step associated with the event.
     */
    JobAndMachineEvent(long time, long job_id, long machine_id, long step_id);

    /**
     * @brief Virtual destructor for the JobAndMachineEvent class.
     */
    ~JobAndMachineEvent() override = 0;

    /**
     * @brief Retrieves the identifier of the step associated with the event.
     * @return The identifier of the associated step.
     */
    [[nodiscard]] long getStepId() const;
};

#endif //SCHEDULING_JOBANDMACHINEEVENT_H
