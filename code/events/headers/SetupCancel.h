//
// Created by mihael on 9/19/23.
//

/**
 * @file SetupCancel.h
 * @brief Defines the SetupCancel class for representing a setup cancellation event in the scheduling simulation.
 */

#ifndef SCHEDULING_SETUPCANCEL_H
#define SCHEDULING_SETUPCANCEL_H

#include "JobAndMachineEvent.h"
#include "Setup.h"

/**
 * @class SetupCancel
 * @brief Represents a setup cancellation event in the scheduling simulation.
 *
 * The SetupCancel class models an event that signifies the cancellation of a setup operation on a machine for a specific job.
 */
class SetupCancel : public JobAndMachineEvent {
private:
    Setup* setup; /**< Pointer to the setup object associated with this event. */

public:
    /**
     * @brief Constructs a SetupCancel object.
     * @param time The time at which the setup operation is canceled.
     * @param job_id The identifier of the job for which the setup is canceled.
     * @param machine_id The identifier of the machine on which the setup was being performed.
     * @param step_id The identifier of the processing step that required the setup (before cancellation).
     * @param setup A pointer to the Setup object containing setup-related information.
     */
    SetupCancel(long time, long job_id, long machine_id, long step_id, Setup* setup);

    /**
     * @brief Retrieves the setup object associated with this event.
     * @return A pointer to the Setup object.
     */
    Setup* getSetup();
};

#endif //SCHEDULING_SETUPCANCEL_H

