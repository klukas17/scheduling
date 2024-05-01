//
// Created by mihael on 4/10/24.
//

#ifndef OFFLINESCHEDULER_H
#define OFFLINESCHEDULER_H
#include "Individual.h"
#include "Scheduler.h"


class OfflineScheduler final : public Scheduler {
    Individual* individual;
    std::map<long, std::map<long, double>> precalculated_scores;
public:
    explicit OfflineScheduler(Individual* individual);
    double calculateScore(long machine_id, long job_id, long step_id) override;
    bool comparePrioritiesOfTwoSteps(long machine_id, long step_id1, long step_id2) override;
    JobProcessingStep* getNextProcessingStep(long job_id) override;
    JobProcessingStep* getProcessingStep(long job_id, long step_id) override;
    bool checkHasJobFinished(long job_id) override;
    [[nodiscard]] Individual* getIndividual() const;
    ~OfflineScheduler() override;
};



#endif //OFFLINESCHEDULER_H
