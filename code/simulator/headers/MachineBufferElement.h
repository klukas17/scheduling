//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineBufferElement.h
 * @brief Defines the MachineBufferElement class for representing an element in a machine's buffer.
 */

#ifndef SCHEDULING_MACHINEBUFFERELEMENT_H
#define SCHEDULING_MACHINEBUFFERELEMENT_H

/**
 * @class MachineBufferElement
 * @brief Represents an element in a machine's buffer.
 *
 * The MachineBufferElement class encapsulates information about an element within a machine's buffer. It stores data
 * related to the step ID and job ID associated with the element, as well as pointers to the previous and next elements
 * within the buffer.
 */
class MachineBufferElement {
public:
    long step_id; /**< The identifier of the processing step associated with the element. */
    long job_id; /**< The identifier of the job associated with the element. */
    long job_type_id; /**< The identifier of the job type associated with the element. */
    long time_start_processing; /**< The time at which processing of the step started. */
    long time_remaining_processing; /**< The remaining time required to complete processing. */
    bool preempt; /**< Flag indicating whether preemption is allowed for this step. */
    MachineBufferElement* prev; /**< A pointer to the previous element in the machine's buffer. */
    MachineBufferElement* next; /**< A pointer to the next element in the machine's buffer. */

    /**
     * @brief Constructs a MachineBufferElement with the provided step and job IDs.
     * @param step_id The identifier of the processing step associated with the element.
     * @param job_id The identifier of the job associated with the element.
     * @param job_type_id The identifier of the job type associated with the element.
     * @param time_start_processing The time at which processing of the step started.
     * @param time_remaining_processing The remaining time required to complete processing.
     * @param preempt Flag indicating whether preemption is allowed for this step.
     */
    MachineBufferElement(long step_id, long job_id, long job_type_id, long time_start_processing, long time_remaining_processing, bool preempt);
};

#endif //SCHEDULING_MACHINEBUFFERELEMENT_H
