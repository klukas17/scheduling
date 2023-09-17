//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineBuffer.h
 * @brief Defines the MachineBuffer class for representing a machine's buffer for job processing steps.
 */

/**
 * @file MachineBuffer.h
 * @brief Defines the MachineBuffer class for representing a machine's buffer for job processing steps.
 */

#ifndef SCHEDULING_MACHINEBUFFER_H
#define SCHEDULING_MACHINEBUFFER_H

#include "MachineBufferElement.h"
#include "vector"
#include "map"
#include "tuple"

/**
 * @class MachineBuffer
 * @brief Represents a machine's buffer for job processing steps.
 *
 * The MachineBuffer class models a buffer associated with a machine that stores job processing steps awaiting execution.
 * It includes attributes and methods to manage the buffer, such as adding steps to the buffer and taking steps from it.
 */
class MachineBuffer {
private:
    MachineBufferElement* head; /**< Pointer to the head element of the buffer. */
    MachineBufferElement* current; /**< Pointer to the current element being processed. */
    std::map<long, long> step_index_to_processing_index; /**< Map of step indices to processing indices. */
    std::map<long, long> processing_index_to_step_index; /**< Map of processing indices to step indices. */
    std::map<long, MachineBufferElement*> step_index_to_node; /**< Map of step indices to buffer nodes. */
    std::map<long, std::tuple<long, long, long, bool>> steps_waiting_for_prerequisites; /**< Map of steps waiting for prerequisites. */

public:
    /**
     * @brief Constructs a MachineBuffer with the preferred processing order.
     * @param preferred_processing_order A vector containing the preferred order of processing steps.
     */
    explicit MachineBuffer(std::vector<long> preferred_processing_order);

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
     * @brief Starts processing the current step in the buffer.
     * @return A pair containing the step ID and the associated job ID of the step being processed.
     */
    std::pair<long, long> startProcessingAStep();

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
     * @brief Sets the time at which processing of the current step started.
     * @param time The time at which processing started.
     */
    void setTimeStartedProcessingForCurrent(long time);

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
     * @brief Moves a processing step from the waiting list to the buffer.
     * @param job_id The identifier of the job associated with the step.
     */
    void moveStepFromWaitingToBuffer(long job_id);

    /**
     * @brief Checks if there are ready jobs in the buffer.
     * @return true if there are ready jobs, false otherwise.
     */
    bool hasReadyJobs();
};

#endif //SCHEDULING_MACHINEBUFFER_H


