//
// Created by mihael on 4/10/24.
//

#include "OfflineScheduler.h"

OfflineScheduler::OfflineScheduler(Individual* individual) {
    this->individual = individual;
    for (auto [machine_id, genotype_node] : individual->getGenotypeNodeMap()) {
        std::map<long, double> machine_precalculated_scores;
        auto step_processing_order = genotype_node->getStepProcessingOrder();
        for (int i = 0; i < step_processing_order.size(); i++) {
            machine_precalculated_scores[step_processing_order[i]] = -i;
        }
        this->precalculated_scores[machine_id] = machine_precalculated_scores;
    }
}

OfflineScheduler::~OfflineScheduler() = default;

Individual* OfflineScheduler::getIndividual() const {
    return individual;
}

double OfflineScheduler::calculateScore(long machine_id, long job_id, long step_id) {
    return precalculated_scores[machine_id][step_id];
}

bool OfflineScheduler::comparePrioritiesOfTwoSteps(long machine_id, long step_id1, long step_id2) {
    return precalculated_scores[machine_id][step_id1] > precalculated_scores[machine_id][step_id2];
}

JobProcessingStep* OfflineScheduler::getProcessingStep(long const job_id, long const step_id) {
    return individual->getProcessingRoute(job_id)->getProcessingStep(step_id);
}

JobProcessingStep* OfflineScheduler::getNextProcessingStep(long const job_id) {
    return individual->getProcessingRoute(job_id)->getNextProcessingStep();
}

bool OfflineScheduler::checkHasJobFinished(long const job_id) {
    return individual->getProcessingRoute(job_id)->checkHasFinished();
}



