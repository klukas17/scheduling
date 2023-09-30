//
// Created by mihael on 9/30/23.
//

/**
 * @file MachineBufferEntryRequestAsynchronous.h
 * @brief Defines the MachineBufferEntryRequestAsynchronous class for representing an asynchronous request for machine
 * buffer entry event in the scheduling simulation.
 */

#ifndef SCHEDULING_MACHINEBUFFERENTRYREQUESTASYNCHRONOUS_H
#define SCHEDULING_MACHINEBUFFERENTRYREQUESTASYNCHRONOUS_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineBufferEntryRequestAsynchronous
 * @brief Represents an asynchronous request for machine buffer entry event in the scheduling simulation.
 *
 * The MachineBufferEntryRequestAsynchronous class is used to represent an asynchronous request for a machine buffer entry
 * event within the scheduling simulation. Such requests are made to add processing steps to a machine's buffer asynchronously.
 */
class MachineBufferEntryRequestAsynchronous : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineBufferEntryRequestAsynchronous object with the specified time, job ID, machine ID, and step ID.
     * @param time The time at which the entry request is made.
     * @param job_id The identifier of the job associated with the entry request.
     * @param machine_id The identifier of the machine for which the entry request is made.
     * @param step_id The identifier of the processing step to be added to the machine's buffer.
     */
    MachineBufferEntryRequestAsynchronous(long time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEBUFFERENTRYREQUESTASYNCHRONOUS_H
