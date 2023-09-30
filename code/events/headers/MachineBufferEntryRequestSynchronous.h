//
// Created by mihael on 9/26/23.
//

/**
 * @file MachineBufferEntryRequestSynchronous.h
 * @brief Defines the MachineBufferEntryRequestSynchronous class for representing a synchronous request for machine
 * buffer entry event in the scheduling simulation.
 */

#ifndef SCHEDULING_MACHINEBUFFERENTRYREQUESTSYNCHRONOUS_H
#define SCHEDULING_MACHINEBUFFERENTRYREQUESTSYNCHRONOUS_H

#include "JobAndMachineEvent.h"

/**
 * @class MachineBufferEntryRequestSynchronous
 * @brief Represents a synchronous request for machine buffer entry event in the scheduling simulation.
 *
 * The MachineBufferEntryRequestSynchronous class is used to represent a synchronous request for a machine buffer entry
 * event within the scheduling simulation. Such requests are made to add processing steps to a machine's buffer synchronously.
 */
class MachineBufferEntryRequestSynchronous : public JobAndMachineEvent {
public:
    /**
     * @brief Constructs a MachineBufferEntryRequestSynchronous object with the provided time, job identifier, machine identifier, and step identifier.
     * @param time The time at which the machine buffer entry event occurs.
     * @param job_id The identifier of the job associated with the event.
     * @param machine_id The identifier of the machine associated with the event.
     * @param step_id The identifier of the step associated with the event.
     */
    MachineBufferEntryRequestSynchronous(long time, long job_id, long machine_id, long step_id);
};


#endif //SCHEDULING_MACHINEBUFFERENTRYREQUESTSYNCHRONOUS_H
