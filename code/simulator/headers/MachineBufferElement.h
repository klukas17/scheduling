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
    MachineBufferElement* prev; /**< A pointer to the previous element in the machine's buffer. */
    MachineBufferElement* next; /**< A pointer to the next element in the machine's buffer. */

    /**
     * @brief Constructs a MachineBufferElement with the provided step and job IDs.
     * @param step_id The identifier of the processing step associated with the element.
     * @param job_id The identifier of the job associated with the element.
     */
    MachineBufferElement(long step_id, long job_id);
};

#endif //SCHEDULING_MACHINEBUFFERELEMENT_H
