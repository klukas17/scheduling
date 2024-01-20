//
// Created by mihael on 10/1/23.
//

/**
 * @file MachineExitBatch.h
 * @brief Defines the MachineExitBatch class for representing a machine exit event associated with batch processing.
 */

#ifndef SCHEDULING_MACHINEEXITBATCH_H
#define SCHEDULING_MACHINEEXITBATCH_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineExitBatch
 * @brief Represents a machine exit event associated with batch processing.
 *
 * The MachineExitBatch class is derived from the JobAndMachineEvent base class and represents an event where a
 * job exits a machine after batch processing.
 */
class MachineExitBatch : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineExitBatch object with the provided time, job ID, machine ID, and step ID.
     * @param time The time at which the machine exit event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine from which the job exits after batch processing.
     * @param step_id The identifier of the processing step associated with the event.
     */
    MachineExitBatch(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEEXITBATCH_H
