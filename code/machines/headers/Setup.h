//
// Created by mihael on 9/19/23.
//

/**
 * @file Setup.h
 * @brief Defines the Setup class for representing setup operations between job types.
 */

#ifndef SCHEDULING_SETUP_H
#define SCHEDULING_SETUP_H

#include "JobType.h"

/**
 * @class Setup
 * @brief Represents a setup operation between two job types.
 *
 * The Setup class models a setup operation that is required when transitioning from one job type to another on a machine.
 * It includes attributes to define the source job type, the destination job type, and the duration of the setup operation.
 */
class Setup {
private:
    JobType* job_type_from; /**< Pointer to the source job type before the setup. */
    JobType* job_type_to; /**< Pointer to the destination job type after the setup. */
    long duration; /**< The duration of the setup operation in time units. */

public:
    /**
     * @brief Constructs a Setup object.
     * @param job_type_from A pointer to the source job type before the setup.
     * @param job_type_to A pointer to the destination job type after the setup.
     * @param duration The duration of the setup operation in time units.
     */
    Setup(JobType* job_type_from, JobType* job_type_to, long duration);

    /**
     * @brief Retrieves the source job type before the setup.
     * @return A pointer to the source JobType.
     */
    JobType* getJobTypeFrom();

    /**
     * @brief Retrieves the destination job type after the setup.
     * @return A pointer to the destination JobType.
     */
    JobType* getJobTypeTo();

    /**
     * @brief Retrieves the duration of the setup operation.
     * @return The duration of the setup operation in time units.
     */
    [[nodiscard]] long getDuration() const;
};

#endif //SCHEDULING_SETUP_H

