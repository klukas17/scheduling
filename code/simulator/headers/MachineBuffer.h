//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEBUFFER_H
#define SCHEDULING_MACHINEBUFFER_H

#include "BatchProcessingScenario.h"
#include "MachineBufferElement.h"
#include "vector"
#include "map"
#include "tuple"

class MachineBuffer {
    MachineBufferElement* head;
    MachineBufferElement* current;
    std::map<long, MachineBufferElement*> current_batch;
    std::map<long, long> step_index_to_processing_index;
    std::map<long, long> processing_index_to_step_index;
    std::map<long, MachineBufferElement*> step_index_to_node;
    std::map<long, std::tuple<long, long, double, double, bool>> steps_waiting_for_prerequisites;
public:
    explicit MachineBuffer(std::vector<long> const & preferred_processing_order);
    void addStepToBuffer(long step_id, long job_id, long job_type_id, double time_start_processing, double time_remaining_processing, bool preempt);
    void startProcessingAStep();
    [[nodiscard]] std::pair<long, long> peekAtFirstProcessingStep() const;
    void finishProcessingAStep();
    void finishProcessingAStepInBatch(long job_id);
    std::tuple<long, long> removeFirstAndRetrieveIt();
    bool checkShouldPreempt();
    [[nodiscard]] std::tuple<long, long> getCurrentStepData() const;
    [[nodiscard]] std::vector<std::tuple<long, long>> getCurrentStepBatchData() const;
    void moveCurrentToBuffer(double time);
    void moveCurrentInBatchToBuffer(double time, long job_id);
    [[nodiscard]] double getRemainingTimeForCurrent() const;
    double getRemainingTimeForCurrentInBatch(long job_id);
    void setTimeStartedProcessingForCurrent(double time) const;
    void setTimeStartedProcessingForCurrentInBatch(double time, long job_id);
    void addStepWaitingForPrerequisite(long step_id, long job_id, long job_type_id, double time_start_processing, double time_remaining_processing, bool preempt);
    void moveStepFromWaitingToBuffer(long job_id);
    [[nodiscard]] bool hasReadyJobs() const;
    [[nodiscard]] bool checkCanPreemptCurrent() const;
    bool comparePrioritiesOfTwoSteps(long step_id1, long step_id2);
    std::vector<std::tuple<long, long>> startBatchProcessing(const BatchProcessingScenario* scenario);
};

#endif //SCHEDULING_MACHINEBUFFER_H
