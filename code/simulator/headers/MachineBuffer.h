//
// Created by mihael on 29/04/23.
//

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
    std::map<long, long> step_index_to_processing_index; /**< Map of step indices to processing indices. */
    std::map<long, long> processing_index_to_step_index; /**< Map of processing indices to step indices. */
    std::map<long, MachineBufferElement*> step_index_to_node; /**< Map of step indices to buffer nodes. */
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
     */
    void addStepToBuffer(long step_id, long job_id);

    /**
     * @brief Takes the next processing step from the machine's buffer.
     * @return A pair containing the step ID and the associated job ID of the taken step.
     */
    std::pair<long, long> takeStepFromBuffer();
};

#endif //SCHEDULING_MACHINEBUFFER_H

