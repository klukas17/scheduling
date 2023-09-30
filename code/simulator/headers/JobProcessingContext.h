//
// Created by mihael on 9/2/23.
//

/**
 * @file JobProcessingContext.h
 * @brief Defines the JobProcessingContext class for representing a job processing context.
 */

#ifndef SCHEDULING_JOBPROCESSINGCONTEXT_H
#define SCHEDULING_JOBPROCESSINGCONTEXT_H

#include "Job.h"
#include "PathNode.h"
#include "map"
#include "stack"
#include "JobProcessingContextFrame.h"
#include "JobProcessingStep.h"
#include "MachineProcessingContext.h"

/**
 * @class JobProcessingContext
 * @brief Represents the processing context for a job within a path node.
 *
 * The JobProcessingContext class encapsulates information related to the processing context of a job
 * within a path node. It includes the job, the current path node, and a stack of frames to track the context's state.
 */
class JobProcessingContext {
private:
    Job* job; /**< A pointer to the job being processed. */
    PathNode* path_node; /**< A pointer to the current path node within the job's paths. */
    JobProcessingStep* job_processing_step; /**< A pointer to the current job processing step. */
    std::stack<JobProcessingContextFrame*> frames; /**< A stack of context frames for managing processing state. */
    long last_processed_path_node_id; /**< The identifier of the last processed path node. */
    bool processing_started; /**< A flag indicating if the processing has started. */
    MachineProcessingContext* previous_machine_processing_context; /**< A pointer to the previous machine's processing context. */

public:
    /**
     * @brief Constructs a JobProcessingContext object for the specified job.
     * @param job A pointer to the job for which the processing context is created.
     */
    explicit JobProcessingContext(Job* job);

    /**
     * @brief Retrieves the job associated with the processing context.
     * @return A pointer to the job being processed.
     */
    Job* getJob();

    /**
     * @brief Retrieves the current path node within the job's paths.
     * @return A pointer to the current path node.
     */
    PathNode* getPathNode();

    /**
     * @brief Sets the current job processing step within the context.
     * @param job_processing_step A pointer to the current job processing step.
     */
    void setJobProcessingStep(JobProcessingStep* job_processing_step);

    /**
     * @brief Moves to the next path node within the job's paths.
     * @param next_machine_id The identifier of the next machine to process the job.
     */
    void moveToNextPathNode(long next_machine_id);

    /**
     * @brief Checks if the current path within the job's paths is finished.
     * @return `true` if the path is finished, `false` otherwise.
     */
    bool checkIfPathFinished();

    /**
     * @brief Retrieves the previous machine's processing context.
     * @return A pointer to the previous machine's processing context.
     */
    MachineProcessingContext* getPreviousMachineProcessingContext();

    /**
     * @brief Sets the previous machine's processing context.
     * @param previous_machine_processing_context A pointer to the previous machine's processing context.
     */
    void setPreviousMachineProcessingContext(MachineProcessingContext* previous_machine_processing_context);
};

#endif //SCHEDULING_JOBPROCESSINGCONTEXT_H
