//
// Created by mihael on 9/19/23.
//

/**
 * @file SetupEnd.h
 * @brief Defines the SetupEnd class for representing a setup end event in the scheduling simulation.
 */

#ifndef SCHEDULING_SETUPEND_H
#define SCHEDULING_SETUPEND_H

#include "JobAndMachineEvent.h"
#include "Setup.h"

/**
 * @class SetupEnd
 * @brief Represents a setup end event in the scheduling simulation.
 *
 * The SetupEnd class models an event that signifies the completion of a setup operation on a machine for a specific job.
 */
class SetupEnd : public JobAndMachineEvent {
private:
    Setup* setup; /**< Pointer to the setup object associated with this event. */

public:
    /**
     * @brief Constructs a SetupEnd object.
     * @param time The time at which the setup operation is completed.
     * @param job_id The identifier of the job for which the setup is finished.
     * @param machine_id The identifier of the machine on which the setup was performed.
     * @param step_id The identifier of the processing step that required the setup.
     * @param setup A pointer to the Setup object containing setup-related information.
     */
    SetupEnd(long time, long job_id, long machine_id, long step_id, Setup* setup);

    /**
     * @brief Retrieves the setup object associated with this event.
     * @return A pointer to the Setup object.
     */
    Setup* getSetup();
};

#endif //SCHEDULING_SETUPEND_H

