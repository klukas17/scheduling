//
// Created by mihael on 30/04/23.
//

/**
 * @file MachineEntry.h
 * @brief Defines the MachineEntry class for representing a machine entry event in the scheduling simulation.
 */

#ifndef SCHEDULING_MACHINEENTRY_H
#define SCHEDULING_MACHINEENTRY_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineEntry
 * @brief Represents a machine entry event in the scheduling simulation.
 *
 * The MachineEntry class is derived from the JobAndMachineEvent class and represents an event that signifies the entry of a job
 * into a machine's processing area in the scheduling system. It includes attributes to store the time of the event, the associated job's identifier,
 * the associated machine's identifier, and the step identifier.
 */
class MachineEntry : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineEntry object with the provided time, job identifier, machine identifier, and step identifier.
     * @param time The time at which the machine entry event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine associated with the event.
     * @param step_id The identifier of the step associated with the event.
     */
    MachineEntry(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEENTRY_H
