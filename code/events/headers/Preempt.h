//
// Created by mihael on 9/17/23.
//

/**
 * @file JobAndMachineEvent.h
 * @brief Defines the JobAndMachineEvent class for representing a preempt event in the scheduling simulation.
 */

#ifndef SCHEDULING_PREEMPT_H
#define SCHEDULING_PREEMPT_H

#include "JobAndMachineEvent.h"

/**
 * @class Preempt
 * @brief Represents a preempt event in the scheduling simulation.
 *
 * The Preempt class is a derived class of JobAndMachineEvent and is used to represent an event
 * when a job is preempted from executing on a machine.
 */
class Preempt : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a Preempt object with the provided time, job identifier, machine identifier, and step identifier.
     * @param time The time at which the machine exit event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine associated with the event.
     * @param step_id The identifier of the step associated with the event.
     */
    Preempt(long time, long job_id, long machine_id, long step_id);
};


#endif //SCHEDULING_PREEMPT_H
