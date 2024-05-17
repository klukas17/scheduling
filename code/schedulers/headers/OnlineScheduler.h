//
// Created by mihael on 4/23/24.
//

#ifndef ONLINESCHEDULER_H
#define ONLINESCHEDULER_H

#include "Job.h"
#include "OnlineSchedulerJobContext.h"
#include "OnlineSchedulerStepIdGenerator.h"
#include "OnlineSchedulingAlgorithmCluster.h"
#include "Scheduler.h"
#include "SchedulerParametersGroup.h"
#include "SchedulerParametersMachine.h"

class OnlineScheduler final : public Scheduler {
    OnlineSchedulingAlgorithmCluster* online_scheduling_algorithm_cluster;
    std::map<long, OnlineSchedulerJobContext*> job_context_map;
    OnlineSchedulerStepIdGenerator* step_id_generator;
    // (machine_id, step_id) -> score
    std::map<long, std::map<long, double>> calculated_scores;
public:
    explicit OnlineScheduler(OnlineSchedulingAlgorithmCluster* online_scheduling_algorithm_cluster);
    void setSimulatorState(SimulatorState* simulator_state) override;
    void intializeJobContexts(const std::map<long, Job*>& jobs);
    double calculateScore(long machine_id, long job_id, long step_id) override;
    bool comparePrioritiesOfTwoSteps(long machine_id, long step_id1, long step_id2) override;
    JobProcessingStep* getNextProcessingStep(long job_id) override;
    JobProcessingStep* getProcessingStep(long job_id, long step_id) override;
    bool checkHasJobFinished(long job_id) override;
    ~OnlineScheduler() override;
};



#endif //ONLINESCHEDULER_H
