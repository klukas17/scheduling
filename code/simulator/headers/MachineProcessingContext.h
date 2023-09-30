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
#include "MachineSetupContext.h"

/**
 * @class MachineProcessingContext
 * @brief Manages a machine's processing context during job execution.
 *
 * The MachineProcessingContext class is responsible for managing the processing context of a machine during job execution.
 * It includes attributes and methods to interact with the machine's processing state, buffer, setup, and related information.
 */
class MachineProcessingContext {
private:
    long machine_id; /**< The identifier of the machine associated with this processing context. */
    GenotypeNode* node; /**< Pointer to the genotype node associated with the machine's processing context. */
    MachineBuffer* machine_buffer; /**< Pointer to the machine's buffer for processing steps. */
    MachineBuffer* machine_buffer_requests; /**< Pointer to the machine's buffer for processing step requests. */
    long buffer_size; /**< The maximum size of the machine's processing buffer. */
    MachineSetupContext* machine_setup_context; /**< Pointer to the machine's setup context. */
    long steps_in_buffer; /**< The number of processing steps currently in the machine's buffer. */
    long steps_in_buffer_requests; /**< The number of processing step requests currently in the buffer. */
    bool currently_working; /**< Flag indicating whether the machine is currently processing a step. */
    bool currently_in_breakdown; /**< Flag indicating whether the machine is currently in a breakdown state. */

public:
    /**
     * @brief Constructs a MachineProcessingContext object associated with the provided machine ID, genotype node, and buffer size.
     * @param machine_id The identifier of the machine associated with this processing context.
     * @param node A pointer to the genotype node associated with the machine's processing context.
     * @param buffer_size The maximum size of the machine's processing buffer.
     */
    MachineProcessingContext(long machine_id, GenotypeNode* node, long buffer_size);

    /**
     * @brief Retrieves the identifier of the machine associated with this processing context.
     * @return The machine identifier.
     */
    [[nodiscard]] long getMachineId() const;

    /**
     * @brief Retrieves the genotype node associated with the machine's processing context.
     * @return A pointer to the associated GenotypeNode object.
     */
    GenotypeNode* getNode();

    /**
     * @brief Retrieves the maximum size of the machine's processing buffer.
     * @return The maximum buffer size.
     */
    [[nodiscard]] long getBufferSize() const;

    /**
     * @brief Adds a processing step to the machine's buffer.
     * @param step_id The identifier of the processing step to be added.
     * @param job_id The identifier of the job associated with the processing step.
     * @param time_start_processing The time at which processing of the step started.
     * @param time_remaining_processing The remaining time required to complete processing.
     * @param preempt Flag indicating whether preemption is allowed for this step.
     */
    void addStepToBuffer(long step_id, long job_id, long time_start_processing, long time_remaining_processing, bool preempt);

    /**
     * @brief Adds a processing step request to the machine's buffer for processing step requests.
     * @param step_id The identifier of the processing step to be added.
     * @param job_id The identifier of the job associated with the processing step.
     * @param time_start_processing The time at which processing of the step started.
     * @param time_remaining_processing The remaining time required to complete processing.
     * @param preempt Flag indicating whether preemption is allowed for this step.
     */
    void addStepToBufferRequests(long step_id, long job_id, long time_start_processing, long time_remaining_processing, bool preempt);

    /**
     * @brief Retrieves the number of processing step requests currently in the machine's buffer for processing step requests.
     * @return The number of processing step requests in the buffer.
     */
    [[nodiscard]] long getStepsInBufferRequests() const;

    /**
     * @brief Removes and retrieves a processing step request from the machine's buffer for processing step requests.
     * @return A tuple containing the step ID and the associated job ID of the removed step.
     */
    std::tuple<long, long> removeStepFromBufferRequests();

    /**
     * @brief Checks if there is space in the machine's processing buffer for additional steps.
     * @return true if the buffer has space, false otherwise.
     */
    [[nodiscard]] bool bufferHasSpace() const;

    /**
     * @brief Adds a processing step to the waiting list for prerequisites.
     * @param step_id The identifier of the processing step.
     * @param job_id The identifier of the job associated with the step.
     * @param time_start_processing The time at which processing of the step started.
     * @param time_remaining_processing The remaining time required to complete processing.
     * @param preempt Flag indicating whether preemption is allowed for this step.
     */
    void addStepWaitingForPrerequisite(long step_id, long job_id, long time_start_processing, long time_remaining_processing, bool preempt);

    /**
     * @brief Moves a processing step from the waiting list to the machine's buffer.
     * @param job_id The identifier of the job associated with the step.
     */
    void moveStepFromWaitingToBuffer(long job_id);

    /**
     * @brief Starts processing the current step in the buffer.
     * @return A pair containing the step ID and the associated job ID of the step being processed.
     */
    std::pair<long, long> startProcessingAStep();

    /**
     * @brief Peeks at the first processing step in the buffer without starting its processing.
     * @return A pair containing the step ID and the associated job ID of the first step in the buffer.
     */
    std::pair<long, long> peekAtFirstProcessingStep();

    /**
     * @brief Finishes processing the current step in the buffer.
     */
    void finishProcessingAStep();

    /**
     * @brief Checks if the current step should be preempted based on priority.
     * @return true if preemption is required, false otherwise.
     */
    bool checkShouldPreempt();

    /**
     * @brief Retrieves data about the current step being processed.
     * @return A tuple containing the step ID and the associated job ID.
     */
    std::tuple<long, long> getCurrentStepData();

    /**
     * @brief Moves the current step from processing to the buffer.
     * @param time The time at which the step is moved back to the buffer.
     */
    void moveCurrentToBuffer(long time);

    /**
     * @brief Retrieves the remaining processing time for the current step.
     * @return The remaining processing time in time units.
     */
    long getRemainingTimeForCurrent();

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

    /**
     * @brief Checks if the machine is currently in a breakdown state.
     * @return true if the machine is in a breakdown state, false otherwise.
     */
    bool isInBreakdown();

    /**
     * @brief Sets the currently in breakdown flag to indicate the machine is in a breakdown state.
     */
    void setCurrentlyInBreakdown();

    /**
     * @brief Unsets the currently in breakdown flag to indicate the machine is no longer in a breakdown state.
     */
    void unsetCurrentlyInBreakdown();

    /**
     * @brief Checks if the current step can be preempted by a higher priority job.
     * @return true if preemption is allowed, false otherwise.
     */
    bool checkCanPreemptCurrent();

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

    /**
     * @brief Compares the priorities of two processing steps.
     * @param step_id1 The identifier of the first processing step.
     * @param step_id2 The identifier of the second processing step.
     * @return true if the first step has a higher priority, false otherwise.
     */
    bool comparePrioritiesOfTwoSteps(long step_id1, long step_id2);

    /**
     * @brief Checks if the machine's buffer has space to accept another job.
     * @return true if the buffer can accept another job, false otherwise.
     */
    [[nodiscard]] bool canAcceptAnotherJobInBuffer() const;
};

#endif // SCHEDULING_MACHINEPROCESSINGCONTEXT_H
