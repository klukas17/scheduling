//
// Created by mihael on 9/25/23.
//

/**
 * @file MachineSetupContext.h
 * @brief Defines the MachineSetupContext class for managing a machine's setup context.
 */

#ifndef SCHEDULING_MACHINESETUPCONTEXT_H
#define SCHEDULING_MACHINESETUPCONTEXT_H

#include "Setup.h"
#include "JobType.h"

/**
 * @class MachineSetupContext
 * @brief Manages a machine's setup context.
 *
 * The MachineSetupContext class is responsible for managing the setup context of a machine. It includes attributes
 * and methods to interact with the machine's setup state, such as the current setup and the last job type processed.
 */
class MachineSetupContext {
private:
    Setup* setup; /**< Pointer to the current setup associated with the machine. */
    JobType* last_job_type; /**< Pointer to the last processed job type. */

public:
    /**
     * @brief Constructs a MachineSetupContext object with default values.
     */
    MachineSetupContext();

    /**
     * @brief Retrieves the current setup associated with the machine.
     * @return A pointer to the Setup object representing the current setup.
     */
    Setup* getSetup();

    /**
     * @brief Sets the current setup for the machine.
     * @param setup A pointer to the Setup object to set as the current setup.
     */
    void setSetup(Setup* setup);

    /**
     * @brief Retrieves the last processed job type.
     * @return A pointer to the JobType object representing the last processed job type.
     */
    JobType* getLastJobType();

    /**
     * @brief Sets the last processed job type.
     * @param last_job_type A pointer to the JobType object representing the last processed job type.
     */
    void setLastJobType(JobType* last_job_type);
};

#endif // SCHEDULING_MACHINESETUPCONTEXT_H
