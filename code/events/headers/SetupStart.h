//
// Created by mihael on 9/19/23.
//

/**
 * @file SetupStart.h
 * @brief Defines the SetupStart class for representing a setup start event in the scheduling simulation.
 */

#ifndef SCHEDULING_SETUPSTART_H
#define SCHEDULING_SETUPSTART_H

#include "JobAndMachineEvent.h"
#include "Setup.h"

/**
 * @class SetupStart
 * @brief Represents a setup start event in the scheduling simulation.
 *
 * The SetupStart class models an event that signifies the start of a setup operation on a machine for a specific job.
 */
class SetupStart : public JobAndMachineEvent {
private:
    Setup* setup; /**< Pointer to the setup object associated with this event. */

public:
    /**
     * @brief Constructs a SetupStart object.
     * @param time The time at which the setup operation starts.
     * @param job_id The identifier of the job for which the setup is initiated.
     * @param machine_id The identifier of the machine on which the setup is performed.
     * @param step_id The identifier of the processing step requiring the setup.
     * @param setup A pointer to the Setup object containing setup-related information.
     */
    SetupStart(long time, long job_id, long machine_id, long step_id, Setup* setup);

    /**
     * @brief Retrieves the setup object associated with this event.
     * @return A pointer to the Setup object.
     */
    Setup* getSetup();
};

#endif //SCHEDULING_SETUPSTART_H

