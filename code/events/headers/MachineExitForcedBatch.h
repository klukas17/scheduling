//
// Created by mihael on 10/1/23.
//

/**
 * @file MachineExitForcedBatch.h
 * @brief Defines the MachineExitForcedBatch class for representing a forced machine exit event associated with batch processing.
 */

#ifndef SCHEDULING_MACHINEEXITFORCEDBATCH_H
#define SCHEDULING_MACHINEEXITFORCEDBATCH_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineExitForcedBatch
 * @brief Represents a forced machine exit event associated with batch processing.
 *
 * The MachineExitForcedBatch class is derived from the JobAndMachineEvent base class and represents an event where a
 * job is forcibly removed from a machine after batch processing, possibly due to external factors or errors.
 */
class MachineExitForcedBatch : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineExitForcedBatch object with the provided time, job ID, machine ID, and step ID.
     * @param time The time at which the forced machine exit event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine from which the job is forcibly removed after batch processing.
     * @param step_id The identifier of the processing step associated with the event.
     */
    MachineExitForcedBatch(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEEXITFORCEDBATCH_H
