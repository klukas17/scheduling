//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineBufferEntry.h
 * @brief Defines the MachineBufferEntry class for representing a machine buffer entry event in the scheduling simulation.
 */

#ifndef SCHEDULING_MACHINEBUFFERENTRY_H
#define SCHEDULING_MACHINEBUFFERENTRY_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineBufferEntry
 * @brief Represents a machine buffer entry event in the scheduling simulation.
 *
 * The MachineBufferEntry class is derived from the JobAndMachineEvent class and represents an event that signifies the entry of a job
 * into a machine's buffer in the scheduling system. It includes attributes to store the time of the event, the associated job's identifier,
 * the associated machine's identifier, and the step identifier.
 */
class MachineBufferEntry : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineBufferEntry object with the provided time, job identifier, machine identifier, and step identifier.
     * @param time The time at which the machine buffer entry event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine associated with the event.
     * @param step_id The identifier of the step associated with the event.
     */
    MachineBufferEntry(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEBUFFERENTRY_H
