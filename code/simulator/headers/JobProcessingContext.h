//
// Created by mihael on 9/2/23.
//

#ifndef SCHEDULING_JOBPROCESSINGCONTEXT_H
#define SCHEDULING_JOBPROCESSINGCONTEXT_H

#include "Job.h"
#include "PathNode.h"
#include "stack"
#include "JobProcessingContextFrame.h"
#include "JobProcessingStep.h"
#include "MachineProcessingContext.h"

class JobProcessingContext {
    Job* job;
    PathNode* path_node;
    PathNode* prev_path_node;
    JobProcessingStep* job_processing_step;
    std::stack<JobProcessingContextFrame*> frames;
    long last_processed_path_node_id;
    bool processing_started;
    MachineProcessingContext* previous_machine_processing_context;
public:
    explicit JobProcessingContext(Job* job);
    ~JobProcessingContext();
    [[nodiscard]] Job* getJob() const;
    [[nodiscard]] PathNode* getPathNode() const;
    void setJobProcessingStep(JobProcessingStep* job_processing_step);
    void moveToNextPathNode(long next_machine_id);
    [[nodiscard]] bool checkIfPathFinished() const;
    [[nodiscard]] MachineProcessingContext* getPreviousMachineProcessingContext() const;
    void setPreviousMachineProcessingContext(MachineProcessingContext* previous_machine_processing_context);
    void markCurrentPathNodeAsCompleted();
    void reduceRemainingProcessingTime(PathNode* path_node, double diff, std::map<long, double>& applied_diffs_map);
    void logRemainingProcessingTimes();
    void logRemainingProcessingTimesForPathNode(PathNode* node, std::set<long>& visited);
};

#endif //SCHEDULING_JOBPROCESSINGCONTEXT_H
