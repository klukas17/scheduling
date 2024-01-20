//
// Created by mihael on 10/1/23.
//

/**
 * @file MachineEntryBatch.h
 * @brief Defines the MachineEntryBatch class for representing a machine entry event associated with batch processing.
 */

#ifndef SCHEDULING_MACHINEENTRYBATCH_H
#define SCHEDULING_MACHINEENTRYBATCH_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineEntryBatch
 * @brief Represents a machine entry event associated with batch processing.
 *
 * The MachineEntryBatch class is derived from the JobAndMachineEvent base class and represents an event where a
 * job enters a machine for processing in a batch.
 */
class MachineEntryBatch : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineEntryBatch object with the provided time, job ID, machine ID, and step ID.
     * @param time The time at which the machine entry event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine where the job enters for processing.
     * @param step_id The identifier of the processing step associated with the event.
     */
    MachineEntryBatch(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEENTRYBATCH_H
