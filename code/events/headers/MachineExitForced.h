//
// Created by mihael on 9/18/23.
//

/**
 * @file MachineExitForced.h
 * @brief Defines the MachineExitForced class for representing a forced machine exit event in the scheduling simulation.
 */

#ifndef SCHEDULING_MACHINEEXITFORCED_H
#define SCHEDULING_MACHINEEXITFORCED_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineExitForced
 * @brief Represents a forced machine exit event in the scheduling simulation.
 *
 * The MachineExitForced class is derived from the JobAndMachineEvent class and represents an event that signifies the forced exit of a job
 * from a machine's processing area in the scheduling system. It includes attributes to store the time of the event, the associated job's identifier,
 * the associated machine's identifier, and the step identifier.
 */
class MachineExitForced : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineExitForced object with the provided time, job identifier, machine identifier, and step identifier.
     * @param time The time at which the machine exit event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine associated with the event.
     * @param step_id The identifier of the step associated with the event.
     */
    MachineExitForced(long time, long job_id, long machine_id, long step_id);
};


#endif //SCHEDULING_MACHINEEXITFORCED_H
