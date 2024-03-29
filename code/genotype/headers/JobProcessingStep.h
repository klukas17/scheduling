//
// Created by mihael on 07/05/23.
//

/**
 * @file JobProcessingStep.h
 * @brief Defines the JobProcessingStep class for representing a processing step within job scheduling.
 */

#ifndef SCHEDULING_JOBPROCESSINGSTEP_H
#define SCHEDULING_JOBPROCESSINGSTEP_H

/**
 * @class JobProcessingStep
 * @brief Represents a processing step within job scheduling.
 *
 * The JobProcessingStep class encapsulates information about a specific processing step in the context of job scheduling.
 * It includes identifiers for the processing step, associated machine, the corresponding job, and a path node identifier.
 */
class JobProcessingStep {
private:
    long processing_step_id; /**< Identifier for the processing step. */
    long machine_id; /**< Identifier for the associated machine. */
    long job_id; /**< Identifier for the corresponding job. */
    long path_node_id; /**< Identifier for the path node associated with this processing step. */

public:
    /**
     * @brief Constructs a JobProcessingStep object with the provided identifiers.
     * @param processing_step_id The identifier for the processing step.
     * @param machine_id The identifier for the associated machine.
     * @param job_id The identifier for the corresponding job.
     * @param path_node_id The identifier for the associated path node.
     */
    JobProcessingStep(long processing_step_id, long machine_id, long job_id, long path_node_id);

    /**
     * @brief Retrieves the identifier for the processing step.
     * @return The identifier for the processing step.
     */
    [[nodiscard]] long getProcessingStepId() const;

    /**
     * @brief Retrieves the identifier for the associated machine.
     * @return The identifier for the associated machine.
     */
    [[nodiscard]] long getMachineId() const;

    /**
     * @brief Retrieves the identifier for the corresponding job.
     * @return The identifier for the corresponding job.
     */
    [[nodiscard]] long getJobId() const;

    /**
     * @brief Retrieves the identifier for the associated path node.
     * @return The identifier for the associated path node.
     */
    [[nodiscard]] long getPathNodeId() const;
};

#endif //SCHEDULING_JOBPROCESSINGSTEP_H
