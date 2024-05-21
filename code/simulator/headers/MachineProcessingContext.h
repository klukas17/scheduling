//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEPROCESSINGCONTEXT_H
#define SCHEDULING_MACHINEPROCESSINGCONTEXT_H

#include "BatchProcessingScenario.h"
#include "GenotypeNode.h"
#include "MachineBuffer.h"
#include "MachineSetupContext.h"
#include "Scheduler.h"

// resolving circular dependencies
class Scheduler;
class MachineBuffer;

class MachineProcessingContext {
    long machine_id;
    Scheduler* scheduler;
    MachineBuffer* machine_buffer;
    MachineBuffer* machine_buffer_requests;
    long buffer_size;
    MachineSetupContext* machine_setup_context;
    long steps_in_buffer;
    long steps_in_buffer_requests;
    bool currently_working;
    bool currently_in_breakdown;
    BatchProcessingScenario* batch_processing_scenario;
    bool batch_processing_started;
public:
    MachineProcessingContext(long machine_id, Scheduler* scheduler, long buffer_size);
    ~MachineProcessingContext();
    [[nodiscard]] long getMachineId() const;
    [[nodiscard]] long getBufferSize() const;
    void addStepToBuffer(long step_id, long job_id, long job_type_id, double time_start_processing, double time_remaining_processing, bool preempt);
    void addStepToBufferRequests(long step_id, long job_id, long job_type_id, double time_start_processing, double time_remaining_processing, bool preempt);
    [[nodiscard]] long getStepsInBufferRequests() const;
    std::tuple<long, long> removeStepFromBufferRequests();
    [[nodiscard]] bool bufferHasSpace() const;
    void addStepWaitingForPrerequisite(long step_id, long job_id, long job_type_id, double time_start_processing, double time_remaining_processing, bool preempt);
    void moveStepFromWaitingToBuffer(long job_id) const;
    void startProcessingAStep() const;
    [[nodiscard]] std::pair<long, long> peekAtFirstProcessingStep() const;
    void finishProcessingAStep();
    void finishProcessingAStepInBatch(long job_id) const;
    [[nodiscard]] bool checkShouldPreempt() const;
    [[nodiscard]] std::tuple<long, long> getCurrentStepData() const;
    [[nodiscard]] std::vector<std::tuple<long, long>> getCurrentStepBatchData() const;
    void moveCurrentToBuffer(double time);
    void moveCurrentInBatchToBuffer(double time, long job_id) const;
    [[nodiscard]] double getRemainingTimeForCurrent() const;
    [[nodiscard]] double getRemainingTimeForCurrentInBatch(long job_id) const;
    void setTimeStartedProcessingForCurrent(double time) const;
    void setTimeStartedProcessingForCurrentInBatch(double time, long job_id) const;
    [[nodiscard]] long getStepsInBuffer() const;
    void decreaseStepsInBuffer();
    [[nodiscard]] bool getCurrentlyWorking() const;
    void setCurrentlyWorking();
    void unsetCurrentlyWorking();
    [[nodiscard]] bool hasReadyJobs() const;
    [[nodiscard]] bool isInBreakdown() const;
    void setCurrentlyInBreakdown();
    void unsetCurrentlyInBreakdown();
    [[nodiscard]] bool checkCanPreemptCurrent() const;
    [[nodiscard]] Setup* getSetup() const;
    void setSetup(Setup* setup) const;
    [[nodiscard]] JobType* getLastJobType() const;
    void setLastJobType(JobType* last_job_type) const;
    [[nodiscard]] bool comparePrioritiesOfTwoSteps(long step_id1, long step_id2) const;
    [[nodiscard]] bool canAcceptAnotherJobInBuffer() const;
    [[nodiscard]] BatchProcessingScenario* getBatchProcessingScenario() const;
    void removeBatchProcessingScenario();
    void setBatchProcessingScenario(BatchProcessingScenario* scenario);
    [[nodiscard]] bool getBatchProcessingStarted() const;
    void setBatchProcessingStarted();
    [[nodiscard]] std::vector<std::tuple<long, long>> startBatchProcessing() const;
    double getRemainingTimeProcessing(long job_id);
};

#endif // SCHEDULING_MACHINEPROCESSINGCONTEXT_H
