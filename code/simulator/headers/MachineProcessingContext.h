//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineProcessingContext.h
 * @brief Defines the MachineProcessingContext class for managing a machine's processing context.
 */

#ifndef SCHEDULING_MACHINEPROCESSINGCONTEXT_H
#define SCHEDULING_MACHINEPROCESSINGCONTEXT_H

#include "GenotypeNode.h"
#include "MachineBuffer.h"

/**
 * @class MachineProcessingContext
 * @brief Manages a machine's processing context during job execution.
 *
 * The MachineProcessingContext class is responsible for managing the processing context of a machine during job execution.
 * It includes attributes and methods to interact with the machine's processing state, buffer, and related information.
 */
class MachineProcessingContext {
private:
    GenotypeNode* node; /**< Pointer to the genotype node associated with the machine's processing context. */
    MachineBuffer* machine_buffer; /**< Pointer to the machine's buffer for processing steps. */
    long steps_in_buffer; /**< The number of processing steps currently in the machine's buffer. */
    bool currently_working; /**< Flag indicating whether the machine is currently processing a step. */
public:
    /**
     * @brief Constructs a MachineProcessingContext object associated with the provided genotype node.
     * @param node A pointer to the genotype node associated with the machine's processing context.
     */
    explicit MachineProcessingContext(GenotypeNode* node);

    /**
     * @brief Retrieves the genotype node associated with the machine's processing context.
     * @return A pointer to the associated GenotypeNode object.
     */
    GenotypeNode* getNode();

    /**
     * @brief Adds a processing step to the machine's buffer.
     * @param step_id The identifier of the processing step to be added.
     * @param job_id The identifier of the job associated with the processing step.
     */
    void addStepToBuffer(long step_id, long job_id);

    /**
     * @brief Adds a processing step to the waiting list for prerequisites.
     * @param step_id The identifier of the processing step.
     * @param job_id The identifier of the job associated with the step.
     */
    void addStepWaitingForPrerequisite(long step_id, long job_id);

    /**
     * @brief Moves a processing step from the waiting list to the machine's buffer.
     * @param job_id The identifier of the job associated with the step.
     */
    void moveStepFromWaitingToBuffer(long job_id);

    /**
     * @brief Takes the next processing step from the machine's buffer.
     * @return A pair containing the step ID and the associated job ID of the taken step.
     */
    std::pair<long, long> takeStepFromBuffer();

    /**
     * @brief Retrieves the number of processing steps currently in the machine's buffer.
     * @return The number of processing steps in the buffer.
     */
    [[nodiscard]] long getStepsInBuffer() const;

    /**
     * @brief Decreases the count of processing steps in the machine's buffer.
     */
    void decreaseStepsInBuffer();

    /**
     * @brief Checks if the machine is currently working on a step.
     * @return True if the machine is currently working, false otherwise.
     */
    [[nodiscard]] bool getCurrentlyWorking() const;

    /**
     * @brief Sets the currently working flag to indicate the machine is processing a step.
     */
    void setCurrentlyWorking();

    /**
     * @brief Unsets the currently working flag to indicate the machine is not processing a step.
     */
    void unsetCurrentlyWorking();

    /**
     * @brief Checks if there are ready jobs in the buffer.
     * @return true if there are ready jobs, false otherwise.
     */
    bool hasReadyJobs();
};

#endif //SCHEDULING_MACHINEPROCESSINGCONTEXT_H
