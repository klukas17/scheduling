//
// Created by mihael on 30/04/23.
//

/**
 * @file MachineExit.h
 * @brief Defines the MachineExit class for representing a machine exit event in the scheduling simulation.
 */

#ifndef SCHEDULING_MACHINEEXIT_H
#define SCHEDULING_MACHINEEXIT_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineExit
 * @brief Represents a machine exit event in the scheduling simulation.
 *
 * The MachineExit class is derived from the JobAndMachineEvent class and represents an event that signifies the exit of a job
 * from a machine's processing area in the scheduling system. It includes attributes to store the time of the event, the associated job's identifier,
 * the associated machine's identifier, and the step identifier.
 */
class MachineExit : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineExit object with the provided time, job identifier, machine identifier, and step identifier.
     * @param time The time at which the machine exit event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine associated with the event.
     * @param step_id The identifier of the step associated with the event.
     */
    MachineExit(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEEXIT_H
