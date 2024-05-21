//
// Created by mihael on 4/23/24.
//

#include "OnlineScheduler.h"
#include "ranges"

OnlineScheduler::OnlineScheduler(OnlineSchedulingAlgorithmCluster* online_scheduling_algorithm_cluster) {
    this->online_scheduling_algorithm_cluster = online_scheduling_algorithm_cluster;
    this->step_id_generator = new OnlineSchedulerStepIdGenerator();
}

OnlineScheduler::~OnlineScheduler() {
    delete step_id_generator;
    for (auto job_context_id : job_context_map | std::views::keys) {
        delete job_context_map[job_context_id];
    }
}

void OnlineScheduler::setSimulatorState(SimulatorState* simulator_state) {
    this->simulator_state = simulator_state;
    for (auto job_context : job_context_map | std::views::values) {
        job_context->setSimulatorState(simulator_state);
    }
}

void OnlineScheduler::intializeJobContexts(const std::map<long, Job*>& jobs) {
    for (auto [job_id, job] : jobs) {
        this->job_context_map[job_id] = new OnlineSchedulerJobContext(job, online_scheduling_algorithm_cluster, step_id_generator);
    }
}

double OnlineScheduler::calculateScore(long machine_id, long job_id, long step_id) {
    auto job = simulator_state->getJob(job_id);
    auto params = new SchedulerParametersMachine(
        job->getReleaseTime(),
        job->getDueTime(),
        job->getWeight(),
        simulator_state->getTime(),
        simulator_state->calculateCombinedWeightsOfBatchCompatibleJobs(machine_id, job_id),
        simulator_state->calculateNumberOfBatchCompatibleJobs(machine_id, job_id),
        simulator_state->calculateBatchProcessingLimit(machine_id, job_id),
        simulator_state->calculateSetupLength(machine_id, job_id),
        simulator_state->calculateTimeUntilNextBreakdown(machine_id, job_id),
        simulator_state->calculatePreemptAllowed(machine_id, job_id)
    );
    auto score = online_scheduling_algorithm_cluster->getAlgorithm(machine_id)->calculateScore(params);
    calculated_scores[machine_id][step_id] = score;
    return score;
}

bool OnlineScheduler::comparePrioritiesOfTwoSteps(long machine_id, long step_id1, long step_id2) {
    return calculated_scores[machine_id][step_id1] > calculated_scores[machine_id][step_id2];
}

JobProcessingStep* OnlineScheduler::getNextProcessingStep(long job_id) {
    return job_context_map[job_id]->getNextProcessingStep();
}

JobProcessingStep* OnlineScheduler::getProcessingStep(long job_id, long step_id) {
    return job_context_map[job_id]->getProcessingStep(step_id);
}

bool OnlineScheduler::checkHasJobFinished(long job_id) {
    return job_context_map[job_id]->checkHasJobFinished();
}
