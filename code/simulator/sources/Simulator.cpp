//
// Created by mihael on 29/04/23.
//

#include "algorithm"
#include "Simulator.h"
#include "queue"
#include "ranges"
#include "fstream"
#include "MachineProcessingContext.h"
#include "JobProcessingContext.h"
#include "JobProcessingPrerequisites.h"
#include "Event.h"
#include "JobAndMachineEvent.h"
#include "SystemEntry.h"
#include "SystemExit.h"
#include "MachineBufferEntry.h"
#include "WakeMachine.h"
#include "MachineEntry.h"
#include "MachineExit.h"
#include "PrerequisitesWaitStart.h"
#include "PrerequisitesWaitEnd.h"
#include "Preempt.h"
#include "BreakdownStart.h"
#include "BreakdownEnd.h"
#include "MachineExitForced.h"
#include "SystemExitForced.h"
#include "SetupStart.h"
#include "SetupEnd.h"
#include "SetupCancel.h"
#include "MachineBufferEntryRequestSynchronous.h"
#include "MachineBufferEntryRequestAsynchronous.h"
#include "MachineEntryBatch.h"
#include "MachineExitBatch.h"
#include "MachineExitForcedBatch.h"
#include "PreemptBatch.h"
#include "SchedulingError.h"
#include "Machine.h"

SimulatorStatistics* Simulator::simulate(Individual *individual, Topology* topology, const std::map<long, Job *> &jobs, bool enable_logging, const std::string &logs_path) {

    auto statistics = SimulatorStatistics();

    double time = 0;
    std::ofstream log_file(logs_path);

    std::deque<Event*> event_queue;

    auto machine_map = individual->getGenotypeNodeMap();

    std::map<long, MachineProcessingContext*> machine_processing_context_map;
    for (const auto& [machine_id, node] : machine_map) {
        machine_processing_context_map[machine_id] = new MachineProcessingContext(
            machine_id,
            node,
            topology->getTopologyElementsMap().at(machine_id)->getBufferSize()
        );
    }

    std::map<long, JobProcessingContext*> job_processing_context_map;
    for (const auto& [job_id, job] : jobs) {
        job_processing_context_map[job_id] = new JobProcessingContext(job);
    }

    auto job_route_map = individual->getProcessingRoutes();

    std::map<long, std::map<long, long>> machine_to_job_times_processed_map;
    for (auto [machine_id, _] : topology->getTopologyElementsMap()) {
        for (auto job_id : jobs | std::views::keys) {
            machine_to_job_times_processed_map[machine_id][job_id] = 0;
        }
    }

    std::vector<JobProcessingPrerequisites*> unfulfilled_job_processing_prerequisites;

    auto comparator = [topology] (MachineEvent* a, MachineEvent* b) {
        long const type1 = a->getEventType();
        long const type2 = b->getEventType();
        if (type1 != type2) {
            return type1 > type2;
        }
        long const id1 = a->getMachineId();
        long const id2 = b->getMachineId();
        if (topology->getPriorityValue(id1, id2) == 1) return true;
        if (topology->getPriorityValue(id1, id2) == -1) return false;
        if (type1 == MACHINE_BUFFER_ENTRY_REQUEST_SYNCHRONOUS && type2 == MACHINE_BUFFER_ENTRY_REQUEST_SYNCHRONOUS) {
            return dynamic_cast<MachineBufferEntryRequestSynchronous*>(a)->getJobId() > dynamic_cast<MachineBufferEntryRequestSynchronous*>(b)->getJobId();
        }
        if (type1 == MACHINE_BUFFER_ENTRY_REQUEST_ASYNCHRONOUS && type2 == MACHINE_BUFFER_ENTRY_REQUEST_ASYNCHRONOUS) {
            return dynamic_cast<MachineBufferEntryRequestAsynchronous*>(a)->getJobId() > dynamic_cast<MachineBufferEntryRequestAsynchronous*>(b)->getJobId();
        }
        return false;
    };
    std::priority_queue<MachineEvent*, std::vector<MachineEvent*>, decltype(comparator)> utility_event_queue(comparator);

    auto addToEventQueue = [](Event *event, std::deque<Event*> &queue) {
        auto const it = std::ranges::upper_bound(queue.begin(), queue.end(), event, [](const Event* a, const Event* b) {
            if (a->getTime() < b->getTime()) return true;
            if (a->getTime() > b->getTime()) return false;
            auto const event_type_a = a->getEventType();
            auto const event_type_b = b->getEventType();
            if ((event_type_a == BREAKDOWN_START || event_type_a == BREAKDOWN_END) && (event_type_b == BREAKDOWN_START || event_type_b == BREAKDOWN_END)) {
                return false;
            }
            return event_type_a < event_type_b;
        });
        queue.insert(it, event);
    };

    auto removeFromEventQueue = [](EventType const event_type, long const job_id, long const machine_id, std::deque<Event*>& queue) {
        auto it = queue.begin();
        while (it != queue.end()) {
            if ((*it)->getEventType() != event_type) {
                ++it;
                continue;
            }
            if (auto const e = dynamic_cast<JobAndMachineEvent*>(*it); e->getJobId() == job_id && e->getMachineId() == machine_id) {
                auto const found_event = *it;
                queue.erase(it);
                delete found_event;
                break;
            }
            ++it;
        }
    };

    auto removeFromEventQueueAnyJob = [](EventType const event_type, long const machine_id, std::deque<Event*>& queue) {
        auto it = queue.begin();
        while (it != queue.end()) {
            if ((*it)->getEventType() != event_type) {
                ++it;
                continue;
            }
            if (auto const e = dynamic_cast<JobAndMachineEvent*>(*it); e->getMachineId() == machine_id) {
                auto const found_event = *it;
                queue.erase(it);
                delete found_event;
                break;
            }
            ++it;
        }
    };

    auto findInEventQueueAnyJob = [](EventType const event_type, long const machine_id, std::deque<Event*>& queue) -> Event* {
        auto it = queue.begin();
        while (it != queue.end()) {
            if ((*it)->getEventType() != event_type) {
                ++it;
                continue;
            }
            if (auto const e = dynamic_cast<JobAndMachineEvent*>(*it); e->getMachineId() == machine_id) {
                return e;
            }
            ++it;
        }
        return nullptr;
    };

    for (auto [job_id, job] : jobs) {
        addToEventQueue(new SystemEntry(job->getReleaseTime(), job_id), event_queue);
        statistics.addJobStatistics(new JobStatistics(job->getId(), job->getReleaseTime(), job->getDueTime(), job->getWeight()));
    }

    for (auto [topology_element_id, topology_element] : topology->getTopologyElementsMap()) {
        for (auto breakdown : topology_element->getBreakdowns()) {
            addToEventQueue(new BreakdownStart(breakdown->getStartTime(), topology_element_id), event_queue);
            addToEventQueue(new BreakdownEnd(breakdown->getEndTime(), topology_element_id), event_queue);
        }
    }

    while (!event_queue.empty() || !utility_event_queue.empty()) {

        if (!event_queue.empty() && (utility_event_queue.empty() || event_queue.front()->getTime() == time)) {

            Event* event = event_queue.front();
            event_queue.pop_front();
            double event_time = event->getTime();
            time = event_time;

            switch (event->getEventType()) {

                case SYSTEM_ENTRY: {
                    auto system_entry_event = dynamic_cast<SystemEntry*>(event);
                    long job_id = system_entry_event->getJobId();
                    auto processing_step = job_route_map[job_id]->getNextProcessingStep();
                    job_processing_context_map[job_id]->setJobProcessingStep(processing_step);
                    long machine_id = processing_step->getMachineId();
                    long step_id = processing_step->getProcessingStepId();
                    utility_event_queue.push(new MachineBufferEntryRequestSynchronous(time, job_id, machine_id, step_id));
                    break;
                }

                case SYSTEM_EXIT: {
                    auto system_exit_event = dynamic_cast<SystemExit*>(event);
                    long job_id = system_exit_event->getJobId();
                    auto job_processing_context = job_processing_context_map[job_id];
                    if (!job_processing_context->checkIfPathFinished()) {
                        throw SchedulingError("Path invalid for job " + std::to_string(job_id));
                    }
                    if (auto previous_machine_processing_context = job_processing_context->getPreviousMachineProcessingContext(); previous_machine_processing_context) {
                        previous_machine_processing_context->decreaseStepsInBuffer();
                        utility_event_queue.push(new WakeMachine(time, previous_machine_processing_context->getMachineId()));
                    }
                    auto job_statistics = statistics.getJobStatistics(job_id);
                    job_statistics->setExitTime(time);
                    job_statistics->setJobStatus(SUCCESSFULLY_TERMINATED);
                    break;
                }

                case MACHINE_BUFFER_ENTRY: {
                    auto machine_buffer_entry_event = dynamic_cast<MachineBufferEntry*>(event);
                    auto job_id = machine_buffer_entry_event->getJobId();
                    long machine_id = machine_buffer_entry_event->getMachineId();
                    long step_id = machine_buffer_entry_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    auto job_processing_context = job_processing_context_map[job_id];
                    job_processing_context->moveToNextPathNode(machine_id);
                    if (auto previous_machine_processing_context = job_processing_context->getPreviousMachineProcessingContext();previous_machine_processing_context) {
                        previous_machine_processing_context->decreaseStepsInBuffer();
                        utility_event_queue.push(new WakeMachine(time, previous_machine_processing_context->getMachineId()));
                    }
                    job_processing_context->setPreviousMachineProcessingContext(machine_processing_context);
                    auto job = jobs.at(job_id);
                    auto processing_duration = job->getProcessingTime(machine_id);
                    bool preempt = job->getJobType()->getPreempt();
                    if (topology->getTopologyElementsMap().at(machine_id)->getTopologyElementType() == MACHINE_TOPOLOGY_ELEMENT) {
                        preempt = preempt && dynamic_cast<Machine*>(topology->getTopologyElementsMap().at(machine_id))->getMachineType()->getPreempt();
                    }
                    if (auto path_tree_node = job->getPathTreeNode(individual->getProcessingRoute(job_id)->getProcessingStep(step_id)->getPathNodeId()); path_tree_node->getPathNode()->getPrerequisites().empty()) {
                        machine_processing_context->addStepToBuffer(step_id, job_id, job->getJobType()->getId(), time, processing_duration, preempt);
                        utility_event_queue.push(new WakeMachine(time, machine_id));
                    }
                    else {
                        machine_processing_context->addStepWaitingForPrerequisite(step_id, job_id, jobs.at(job_id)->getJobType()->getId(), time, processing_duration, preempt);
                        addToEventQueue(new PrerequisitesWaitStart(time, job_id, machine_id, step_id), event_queue);
                        utility_event_queue.push(new WakeMachine(time, machine_id));
                    }
                    break;
                }

                case MACHINE_ENTRY: {
                    auto machine_entry_event = dynamic_cast<MachineEntry*>(event);
                    long job_id = machine_entry_event->getJobId();
                    long machine_id = machine_entry_event->getMachineId();
                    long step_id = machine_entry_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->setCurrentlyWorking();
                    machine_processing_context->startProcessingAStep();
                    machine_processing_context->setLastJobType(jobs.at(job_id)->getJobType());
                    machine_processing_context->setTimeStartedProcessingForCurrent(time);
                    auto processing_duration = machine_processing_context->getRemainingTimeForCurrent();
                    addToEventQueue(new MachineExit(time + processing_duration, job_id, machine_id, step_id), event_queue);
                    if (auto const topology_element = topology->getTopologyElementsMap().at(machine_id); topology_element->getTopologyElementType() == MACHINE_TOPOLOGY_ELEMENT) {
                        auto machine = dynamic_cast<Machine*>(topology_element);
                        if (auto const batch_processing_scenario = machine->getMachineType()->getBatchProcessingScenarioRules()->findBatchProcessingScenario(jobs.at(job_id)->getJobType()->getId()); batch_processing_scenario) {
                            machine_processing_context->setBatchProcessingScenario(batch_processing_scenario);
                            utility_event_queue.push(new WakeMachine(time, machine_id));
                        }
                    }
                    break;
                }

                case MACHINE_EXIT: {
                    auto machine_exit_event = dynamic_cast<MachineExit*>(event);
                    long job_id = machine_exit_event->getJobId();
                    long machine_id = machine_exit_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    if (auto const job_route = job_route_map[job_id]; job_route->checkHasFinished()) {
                        job_processing_context_map[job_id]->setJobProcessingStep(nullptr);
                        addToEventQueue(new SystemExit(time, job_id), event_queue);
                    }
                    else {
                        auto processing_step = job_route->getNextProcessingStep();
                        job_processing_context_map[job_id]->setJobProcessingStep(processing_step);
                        long next_machine_id = processing_step->getMachineId();
                        long next_step_id = processing_step->getProcessingStepId();
                        utility_event_queue.push(new MachineBufferEntryRequestAsynchronous(time, job_id, next_machine_id, next_step_id));
                    }
                    machine_processing_context->finishProcessingAStep();
                    machine_processing_context->removeBatchProcessingScenario();
                    utility_event_queue.push(new WakeMachine(time, machine_id));
                    machine_to_job_times_processed_map[machine_id][job_id]++;
                    auto it = unfulfilled_job_processing_prerequisites.begin();
                    while (it != unfulfilled_job_processing_prerequisites.end()) {
                        auto job_processing_prerequisite = *it;
                        job_processing_prerequisite->updatePrerequisites(machine_id, job_id, machine_to_job_times_processed_map[machine_id][job_id]);
                        if (job_processing_prerequisite->checkAllPrerequisitesSatisfied()) {
                            it = unfulfilled_job_processing_prerequisites.erase(it);
                            auto prerequisite_job_id = job_processing_prerequisite->getJobId();
                            auto prerequisite_machine_id = job_processing_prerequisite->getMachineId();
                            auto prerequisite_step_id = job_processing_prerequisite->getStepId();
                            delete job_processing_prerequisite;
                            addToEventQueue(new PrerequisitesWaitEnd(time, prerequisite_job_id, prerequisite_machine_id, prerequisite_step_id), event_queue);
                        }
                        else {
                            ++it;
                        }
                    }
                    break;
                }

                case PREREQUISITES_WAIT_START: {
                    auto prerequisite_wait_start_event = dynamic_cast<PrerequisitesWaitStart*>(event);
                    long job_id = prerequisite_wait_start_event->getJobId();
                    long machine_id = prerequisite_wait_start_event->getMachineId();
                    long step_id = prerequisite_wait_start_event->getStepId();
                    auto job = jobs.at(job_id);
                    auto path_tree_node = job->getPathTreeNode(individual->getProcessingRoute(job_id)->getProcessingStep(step_id)->getPathNodeId());
                    auto job_processing_prerequisites = new JobProcessingPrerequisites(job_id, machine_id, step_id, path_tree_node->getPathNode()->getPrerequisites());
                    for (auto [machine_id, _] : topology->getTopologyElementsMap()) {
                        for (auto other_job_id : jobs | std::views::keys) {
                            job_processing_prerequisites->updatePrerequisites(machine_id, other_job_id, machine_to_job_times_processed_map[machine_id][other_job_id]);
                        }
                    }
                    if (job_processing_prerequisites->checkAllPrerequisitesSatisfied()) {
                        delete job_processing_prerequisites;
                        addToEventQueue(new PrerequisitesWaitEnd(time, job_id, machine_id, step_id), event_queue);
                    }
                    else {
                        unfulfilled_job_processing_prerequisites.push_back(job_processing_prerequisites);
                    }
                    break;
                }

                case PREREQUISITES_WAIT_END: {
                    auto prerequisite_wait_end_event = dynamic_cast<PrerequisitesWaitEnd*>(event);
                    long job_id = prerequisite_wait_end_event->getJobId();
                    long machine_id = prerequisite_wait_end_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->moveStepFromWaitingToBuffer(job_id);
                    utility_event_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case PREEMPT: {
                    auto preempt_event = dynamic_cast<Preempt*>(event);
                    long job_id = preempt_event->getJobId();
                    long machine_id = preempt_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->moveCurrentToBuffer(time);
                    removeFromEventQueue(MACHINE_EXIT, job_id, machine_id, event_queue);
                    utility_event_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case BREAKDOWN_START: {
                    auto breakdown_start_event = dynamic_cast<BreakdownStart*>(event);
                    long machine_id = breakdown_start_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->setCurrentlyInBreakdown();
                    if (machine_processing_context->getCurrentlyWorking()) {
                        auto [job_id, step_id] = machine_processing_context->getCurrentStepData();
                        auto steps_in_batch = machine_processing_context->getCurrentStepBatchData();
                        if (machine_processing_context->checkCanPreemptCurrent()) {
                            addToEventQueue(new Preempt(time, job_id, machine_id, step_id), event_queue);
                            for (auto step_in_batch : steps_in_batch) {
                                addToEventQueue(new PreemptBatch(time, std::get<0>(step_in_batch), machine_id, std::get<1>(step_in_batch)), event_queue);
                            }
                        }
                        else {
                            addToEventQueue(new MachineExitForced(time, job_id, machine_id, step_id), event_queue);
                            for (auto step_in_batch : steps_in_batch) {
                                addToEventQueue(new MachineExitForcedBatch(time, std::get<0>(step_in_batch), machine_id, std::get<1>(step_in_batch)), event_queue);
                            }
                        }
                    }
                    if (machine_processing_context->getSetup()) {
                        auto [step_id, job_id] = machine_processing_context->peekAtFirstProcessingStep();
                        addToEventQueue(new SetupCancel(time, job_id, machine_id, step_id, machine_processing_context->getSetup()), event_queue);
                    }
                    removeFromEventQueueAnyJob(MACHINE_ENTRY, machine_id, event_queue);
                    break;
                }

                case BREAKDOWN_END: {
                    auto breakdown_end_event = dynamic_cast<BreakdownEnd*>(event);
                    long machine_id = breakdown_end_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->unsetCurrentlyInBreakdown();
                    utility_event_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case SETUP_START: {
                    auto setup_start_event = dynamic_cast<SetupStart*>(event);
                    long job_id = setup_start_event->getJobId();
                    long machine_id = setup_start_event->getMachineId();
                    long step_id = setup_start_event->getStepId();
                    auto setup = setup_start_event->getSetup();
                    addToEventQueue(new SetupEnd(time + setup->getDuration(), job_id, machine_id, step_id, setup), event_queue);
                    break;
                }

                case SETUP_END: {
                    auto setup_end_event = dynamic_cast<SetupEnd*>(event);
                    long job_id = setup_end_event->getJobId();
                    long machine_id = setup_end_event->getMachineId();
                    long step_id = setup_end_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    addToEventQueue(new MachineEntry(time, job_id, machine_id, step_id), event_queue);
                    machine_processing_context->setSetup(nullptr);
                    break;
                }

                case SETUP_CANCEL: {
                    auto setup_cancel_event = dynamic_cast<SetupCancel*>(event);
                    long job_id = setup_cancel_event->getJobId();
                    long machine_id = setup_cancel_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    removeFromEventQueue(SETUP_END, job_id, machine_id, event_queue);
                    machine_processing_context->setSetup(nullptr);
                    utility_event_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case MACHINE_EXIT_FORCED: {
                    auto machine_exit_forced_event = dynamic_cast<MachineExitForced*>(event);
                    long job_id = machine_exit_forced_event->getJobId();
                    long machine_id = machine_exit_forced_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->finishProcessingAStep();
                    utility_event_queue.push(new WakeMachine(time, machine_id));
                    removeFromEventQueue(MACHINE_EXIT, job_id, machine_id, event_queue);
                    addToEventQueue(new SystemExitForced(time, job_id), event_queue);
                    break;
                }

                case SYSTEM_EXIT_FORCED: {
                    auto system_exit_forced_event = dynamic_cast<SystemExitForced*>(event);
                    long job_id = system_exit_forced_event->getJobId();
                    auto job_processing_context = job_processing_context_map[job_id];
                    if (auto previous_machine_processing_context = job_processing_context->getPreviousMachineProcessingContext(); previous_machine_processing_context) {
                        previous_machine_processing_context->decreaseStepsInBuffer();
                        utility_event_queue.push(new WakeMachine(time, previous_machine_processing_context->getMachineId()));
                    }
                    auto job_statistics = statistics.getJobStatistics(job_id);
                    job_statistics->setExitTime(time);
                    job_statistics->setJobStatus(FORCEFULLY_TERMINATED);
                    break;
                }

                case MACHINE_ENTRY_BATCH: {
                    auto machine_entry_batch_event = dynamic_cast<MachineEntryBatch*>(event);
                    long job_id = machine_entry_batch_event->getJobId();
                    long machine_id = machine_entry_batch_event->getMachineId();
                    long step_id = machine_entry_batch_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->setTimeStartedProcessingForCurrentInBatch(time, job_id);
                    auto processing_duration = machine_processing_context->getRemainingTimeForCurrentInBatch(job_id);
                    addToEventQueue(new MachineExitBatch(time + processing_duration, job_id, machine_id, step_id), event_queue);
                    break;
                }

                case MACHINE_EXIT_BATCH: {
                    auto machine_exit_batch_event = dynamic_cast<MachineExitBatch*>(event);
                    long job_id = machine_exit_batch_event->getJobId();
                    long machine_id = machine_exit_batch_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    if (auto const job_route = job_route_map[job_id]; job_route->checkHasFinished()) {
                        job_processing_context_map[job_id]->setJobProcessingStep(nullptr);
                        addToEventQueue(new SystemExit(time, job_id), event_queue);
                    }
                    else {
                        auto processing_step = job_route->getNextProcessingStep();
                        job_processing_context_map[job_id]->setJobProcessingStep(processing_step);
                        long next_machine_id = processing_step->getMachineId();
                        long next_step_id = processing_step->getProcessingStepId();
                        utility_event_queue.push(new MachineBufferEntryRequestAsynchronous(time, job_id, next_machine_id, next_step_id));
                    }
                    machine_processing_context->finishProcessingAStepInBatch(job_id);
                    machine_to_job_times_processed_map[machine_id][job_id]++;
                    auto it = unfulfilled_job_processing_prerequisites.begin();
                    while (it != unfulfilled_job_processing_prerequisites.end()) {
                        auto job_processing_prerequisite = *it;
                        job_processing_prerequisite->updatePrerequisites(machine_id, job_id, machine_to_job_times_processed_map[machine_id][job_id]);
                        if (job_processing_prerequisite->checkAllPrerequisitesSatisfied()) {
                            it = unfulfilled_job_processing_prerequisites.erase(it);
                            auto prerequisite_job_id = job_processing_prerequisite->getJobId();
                            auto prerequisite_machine_id = job_processing_prerequisite->getMachineId();
                            auto prerequisite_step_id = job_processing_prerequisite->getStepId();
                            delete job_processing_prerequisite;
                            addToEventQueue(new PrerequisitesWaitEnd(time, prerequisite_job_id, prerequisite_machine_id, prerequisite_step_id), event_queue);
                        }
                        else {
                            ++it;
                        }
                    }
                    break;
                }

                case MACHINE_EXIT_FORCED_BATCH: {
                    auto machine_exit_forced_batch_event = dynamic_cast<MachineExitForcedBatch*>(event);
                    long job_id = machine_exit_forced_batch_event->getJobId();
                    long machine_id = machine_exit_forced_batch_event->getMachineId();
                    removeFromEventQueue(MACHINE_EXIT_BATCH, job_id, machine_id, event_queue);
                    addToEventQueue(new SystemExitForced(time, job_id), event_queue);
                    break;
                }

                case PREEMPT_BATCH: {
                    auto preempt_batch_event = dynamic_cast<PreemptBatch*>(event);
                    long job_id = preempt_batch_event->getJobId();
                    long machine_id = preempt_batch_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->moveCurrentInBatchToBuffer(time, job_id);
                    removeFromEventQueue(MACHINE_EXIT_BATCH, job_id, machine_id, event_queue);
                    break;
                }

                case ABSTRACT:
                    throw SchedulingError("Abstract event encountered in the event_queue in Simulator::simulate function.");

                case WAKE_MACHINE:
                    throw SchedulingError("Wake machine event encountered in the event_queue in Simulator::simulate function.");

                case MACHINE_BUFFER_ENTRY_REQUEST_SYNCHRONOUS:
                    throw SchedulingError("Synchronous machine buffer entry request event encountered in the event_queue in Simulator::simulate function.");

                case MACHINE_BUFFER_ENTRY_REQUEST_ASYNCHRONOUS:
                    throw SchedulingError("Asynchronous machine buffer entry request event encountered in the event_queue in Simulator::simulate function.");

            }

            if (enable_logging && !event->getMessage().empty()) {
                log_file << "[" << time << "] " << event->getMessage() << std::endl;
            }

            delete event;
        }

        else {

            auto event = utility_event_queue.top();
            utility_event_queue.pop();

            switch (event->getEventType()) {

                case ABSTRACT:
                case SYSTEM_ENTRY:
                case SYSTEM_EXIT:
                case MACHINE_BUFFER_ENTRY:
                case MACHINE_ENTRY:
                case MACHINE_EXIT:
                case PREREQUISITES_WAIT_START:
                case PREREQUISITES_WAIT_END:
                case PREEMPT:
                case BREAKDOWN_START:
                case BREAKDOWN_END:
                case SETUP_START:
                case SETUP_END:
                case SETUP_CANCEL:
                case MACHINE_EXIT_FORCED:
                case SYSTEM_EXIT_FORCED:
                case MACHINE_ENTRY_BATCH:
                case MACHINE_EXIT_BATCH:
                case MACHINE_EXIT_FORCED_BATCH:
                case PREEMPT_BATCH:
                    throw SchedulingError("Non utility event encountered in the utility_event_queue in Simulator::simulate function.");

                case WAKE_MACHINE: {
                    auto wake_machine_event = dynamic_cast<WakeMachine*>(event);
                    long machine_id = wake_machine_event->getMachineId();
                    MachineProcessingContext* machine_processing_context = machine_processing_context_map[machine_id];
                    if (machine_processing_context->bufferHasSpace() && machine_processing_context->getStepsInBufferRequests() > 0) {
                        auto [step_id, job_id] = machine_processing_context->removeStepFromBufferRequests();
                        addToEventQueue(new MachineBufferEntry(time, job_id, machine_id, step_id), event_queue);
                        break;
                    }
                    if (!machine_processing_context->hasReadyJobs() || machine_processing_context->isInBreakdown()) {
                        break;
                    }
                    if (!machine_processing_context->getCurrentlyWorking()) {
                        auto [step_id, job_id] = machine_processing_context->peekAtFirstProcessingStep();
                        if (auto setup = machine_processing_context->getSetup(); setup != nullptr) {
                            if (auto setup_end_event = dynamic_cast<SetupEnd*>(findInEventQueueAnyJob(SETUP_END, machine_id, event_queue)); setup_end_event != nullptr) {
                                long setup_step_id = setup_end_event->getStepId();
                                long setup_job_id = setup_end_event->getJobId();
                                if (bool should_cancel_setup = machine_processing_context->comparePrioritiesOfTwoSteps(step_id, setup_step_id); should_cancel_setup) {
                                    addToEventQueue(new SetupCancel(time, setup_job_id, machine_id, setup_step_id, machine_processing_context->getSetup()), event_queue);
                                }
                            }
                            else {
                                throw SchedulingError("Setup start event without setup end event pair found in Simulator::simulate function.");
                            }
                            break;
                        }
                        if (auto topology_element = topology->getTopologyElementsMap().at(machine_id); topology_element->getTopologyElementType() == MACHINE_TOPOLOGY_ELEMENT) {
                            auto machine = dynamic_cast<Machine*>(topology_element);
                            auto setup_rules = machine->getMachineType()->getSetupRules();
                            auto last_job_type = machine_processing_context->getLastJobType();
                            auto job_type = jobs.at(job_id)->getJobType();
                            if (auto new_setup = setup_rules->findSetup(last_job_type ? last_job_type->getId() : -1, job_type->getId()); new_setup) {
                                machine_processing_context->setSetup(new_setup);
                                addToEventQueue(new SetupStart(time, job_id, machine_id, step_id, new_setup), event_queue);
                                break;
                            }
                        }
                        addToEventQueue(new MachineEntry(time, job_id, machine_id, step_id), event_queue);
                    }
                    else if (machine_processing_context->checkShouldPreempt()) {
                        auto [job_id, step_id] = machine_processing_context->getCurrentStepData();
                        auto steps_in_batch = machine_processing_context->getCurrentStepBatchData();
                        addToEventQueue(new Preempt(time, job_id, machine_id, step_id), event_queue);
                        for (auto step_in_batch : steps_in_batch) {
                            addToEventQueue(new PreemptBatch(time, std::get<0>(step_in_batch), machine_id, std::get<1>(step_in_batch)), event_queue);
                        }
                    }
                    if (!machine_processing_context->getBatchProcessingStarted()) {
                        for (auto const batch_jobs_started = machine_processing_context->startBatchProcessing(); auto job : batch_jobs_started) {
                            addToEventQueue(new MachineEntryBatch(time, std::get<1>(job), machine_id, std::get<0>(job)), event_queue);
                        }
                        machine_processing_context->setBatchProcessingStarted();
                    }
                    break;
                }

                case MACHINE_BUFFER_ENTRY_REQUEST_SYNCHRONOUS: {
                    auto machine_buffer_entry_request_synchronous_event = dynamic_cast<MachineBufferEntryRequestSynchronous*>(event);
                    long job_id = machine_buffer_entry_request_synchronous_event->getJobId();
                    long machine_id = machine_buffer_entry_request_synchronous_event->getMachineId();
                    long step_id = machine_buffer_entry_request_synchronous_event->getStepId();
                    if (auto machine_processing_context = machine_processing_context_map[machine_id]; machine_processing_context->bufferHasSpace()) {
                        addToEventQueue(new MachineBufferEntry(time, job_id, machine_id, step_id), event_queue);
                    }
                    else {
                        addToEventQueue(new SystemExitForced(time, job_id), event_queue);
                    }
                    break;
                }

                case MACHINE_BUFFER_ENTRY_REQUEST_ASYNCHRONOUS: {
                    auto machine_buffer_entry_request_asynchronous_event = dynamic_cast<MachineBufferEntryRequestAsynchronous*>(event);
                    long job_id = machine_buffer_entry_request_asynchronous_event->getJobId();
                    long machine_id = machine_buffer_entry_request_asynchronous_event->getMachineId();
                    long step_id = machine_buffer_entry_request_asynchronous_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    auto job = jobs.at(job_id);
                    auto processing_duration = job->getProcessingTime(machine_id);
                    bool preempt = job->getJobType()->getPreempt();
                    if (topology->getTopologyElementsMap().at(machine_id)->getTopologyElementType() == MACHINE_TOPOLOGY_ELEMENT) {
                        preempt = preempt && dynamic_cast<Machine*>(topology->getTopologyElementsMap().at(machine_id))->getMachineType()->getPreempt();
                    }
                    if (machine_processing_context->bufferHasSpace()) {
                        addToEventQueue(new MachineBufferEntry(time, job_id, machine_id, step_id), event_queue);
                    }
                    else {
                        machine_processing_context->addStepToBufferRequests(step_id, job_id, job->getJobType()->getId(), time, processing_duration, preempt);
                    }
                    break;
                }

            }

            delete event;
        }
    }

    log_file.close();
}