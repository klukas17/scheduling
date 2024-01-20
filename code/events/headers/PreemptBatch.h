//
// Created by mihael on 10/1/23.
//

/**
 * @file PreemptBatch.h
 * @brief Defines the PreemptBatch class for representing a preemption event associated with batch processing.
 */

#ifndef SCHEDULING_PREEMPTBATCH_H
#define SCHEDULING_PREEMPTBATCH_H

#include "JobAndMachineEvent.h"

/**
 * @class PreemptBatch
 * @brief Represents a preemption event associated with batch processing.
 *
 * The PreemptBatch class is derived from the JobAndMachineEvent base class and represents an event where a
 * job is preempted from a machine during batch processing, possibly due to higher-priority jobs or scheduling policies.
 */
class PreemptBatch : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a PreemptBatch object with the provided time, job ID, machine ID, and step ID.
     * @param time The time at which the preemption event occurs.
     * @param job_id The identifier of the job associated with the preemption event.
     * @param machine_id The identifier of the machine from which the job is preempted during batch processing.
     * @param step_id The identifier of the processing step associated with the event.
     */
    PreemptBatch(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_PREEMPTBATCH_H
