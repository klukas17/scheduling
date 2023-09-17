//
// Created by mihael on 9/16/23.
//

/**
 * @file JobProcessingPrerequisites.h
 * @brief Defines the JobProcessingPrerequisites class for managing prerequisites of a job processing step.
 */

#ifndef SCHEDULING_JOBPROCESSINGPREREQUISITES_H
#define SCHEDULING_JOBPROCESSINGPREREQUISITES_H

#include "vector"
#include "Prerequisite.h"

/**
 * @class JobProcessingPrerequisites
 * @brief Manages prerequisites of a job processing step.
 *
 * The JobProcessingPrerequisites class is responsible for managing and tracking prerequisites associated with a job's
 * processing step. It keeps track of whether these prerequisites have been satisfied and provides methods for updating
 * and checking their status.
 */
class JobProcessingPrerequisites {
private:
    long job_id; /**< Identifier for the job. */
    long machine_id; /**< Identifier for the machine where the step will be executed. */
    long step_id; /**< Identifier for the job processing step. */
    std::vector<Prerequisite*> prerequisites; /**< Vector of prerequisite objects. */
    std::vector<bool> prerequisites_satisfied; /**< Vector indicating whether each prerequisite is satisfied. */
public:
    /**
     * @brief Constructs a JobProcessingPrerequisites object with the specified parameters.
     * @param job_id The identifier for the job.
     * @param machine_id The identifier for the machine where the step will be executed.
     * @param step_id The identifier for the job processing step.
     * @param prerequisites A vector of prerequisite objects.
     */
    JobProcessingPrerequisites(long job_id, long machine_id, long step_id, const std::vector<Prerequisite*>& prerequisites);

    /**
     * @brief Retrieves the identifier for the job.
     * @return The identifier for the job.
     */
    [[nodiscard]] long getJobId() const;

    /**
     * @brief Retrieves the identifier for the machine where the step will be executed.
     * @return The identifier for the machine.
     */
    [[nodiscard]] long getMachineId() const;

    /**
     * @brief Retrieves the identifier for the job processing step.
     * @return The identifier for the step.
     */
    [[nodiscard]] long getStepId() const;

    /**
     * @brief Updates the prerequisites based on machine and job IDs, and repetitions.
     * @param machine_id The identifier of the machine.
     * @param job_id The identifier of the job.
     * @param repetitions The number of repetitions to update prerequisites.
     */
    void updatePrerequisites(long machine_id, long job_id, long repetitions);

    /**
     * @brief Checks if all prerequisites are satisfied.
     * @return true if all prerequisites are satisfied, false otherwise.
     */
    bool checkAllPrerequisitesSatisfied();
};

#endif //SCHEDULING_JOBPROCESSINGPREREQUISITES_H
