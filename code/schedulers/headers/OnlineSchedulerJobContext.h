//
// Created by mihael on 5/7/24.
//

#ifndef ONLINESCHEDULERJOBCONTEXT_H
#define ONLINESCHEDULERJOBCONTEXT_H

#include <map>
#include <stack>
#include "Job.h"
#include "JobProcessingStep.h"
#include "OnlineSchedulerStepIdGenerator.h"
#include "OnlineSchedulingAlgorithmCluster.h"
#include "PathNode.h"
#include "SimulatorState.h"


class OnlineSchedulerJobContext {
    long job_id;
    Job* job;
    std::map<long, JobProcessingStep*> processing_steps_map;
    JobProcessingStep* current_processing_step;
    std::stack<std::vector<PathNode*>> path_node_stack;
    OnlineSchedulingAlgorithmCluster* algorithm_cluster;
    OnlineSchedulerStepIdGenerator* step_id_generator;
    std::map<long, OnlineSchedulingAlgorithm*> algorithms_cache;
    SimulatorState* simulator_state;
    std::set<long> open_group_path_nodes;
public:
    OnlineSchedulerJobContext(Job* job, OnlineSchedulingAlgorithmCluster* algorithm_cluster, OnlineSchedulerStepIdGenerator* step_id_generator);
    JobProcessingStep* getNextProcessingStep();
    JobProcessingStep* getProcessingStep(long step_id);
    bool checkHasJobFinished();
    void setSimulatorState(SimulatorState* simulator_state);
};



#endif //ONLINESCHEDULERJOBCONTEXT_H
