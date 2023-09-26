//
// Created by mihael on 29/04/23.
//

/**
 * @file Simulator.cpp
 * @brief Implements the member functions of the Simulator class.
 */

#include <algorithm>
#include "Simulator.h"
#include "queue"
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
#include "SchedulingError.h"
#include "Machine.h"

void Simulator::simulate(Individual *individual, Topology* topology, const std::map<long, Job *> &jobs, bool enable_logging, const std::string &logs_path) {

    long time = 0;
    std::ofstream log_file(logs_path);

    std::deque<Event*> event_queue;

    auto machine_map = individual->getGenotypeNodeMap();

    std::map<long, MachineProcessingContext*> machine_processing_context_map;
    for (auto entry : machine_map) {
        machine_processing_context_map[entry.first] = new MachineProcessingContext(entry.second);
    }

    std::map<long, JobProcessingContext*> job_processing_context_map;
    for (auto entry : jobs) {
        job_processing_context_map[entry.first] = new JobProcessingContext(entry.second);
    }

    auto job_route_map = individual->getProcessingRoutes();

    std::map<long, std::map<long, long>> machine_to_job_times_processed_map;
    for (auto machine_pair : topology->getTopologyElementsMap()) {
        for (auto job_pair : jobs) {
            machine_to_job_times_processed_map[machine_pair.first][job_pair.first] = 0;
        }
    }

    std::vector<JobProcessingPrerequisites*> unfulfilled_job_processing_prerequisites;

    auto comparator = [topology] (WakeMachine* a, WakeMachine* b) {
        long id1 = a->getMachineId();
        long id2 = b->getMachineId();
        if (topology->getPriorityValue(id1, id2) == 1) return true;
        if (topology->getPriorityValue(id1, id2) == -1) return false;
        return true;
    };
    std::priority_queue<WakeMachine*, std::vector<WakeMachine*>, decltype(comparator)> wake_machines_queue(comparator);

    auto addToEventQueue = [](Event *event, std::deque<Event*> &event_queue) {
        auto it = std::upper_bound(event_queue.begin(), event_queue.end(), event, [](const Event* a, const Event* b) {
            if (a->getTime() < b->getTime()) return true;
            else if (a->getTime() > b->getTime()) return false;
            auto event_type_a = a->getEventType();
            auto event_type_b = b->getEventType();
            if ((event_type_a == BREAKDOWN_START || event_type_a == BREAKDOWN_END) && (event_type_b == BREAKDOWN_START || event_type_b == BREAKDOWN_END)) {
                return false;
            }
            return event_type_a < event_type_b;
        });
        event_queue.insert(it, event);
    };

    auto removeFromEventQueue = [](EventType event_type, long job_id, long machine_id, std::deque<Event*>& event_queue) {
        auto it = event_queue.begin();
        while (it != event_queue.end()) {
            if ((*it)->getEventType() != event_type) {
                it++;
                continue;
            }
            auto e = dynamic_cast<JobAndMachineEvent*>(*it);
            if (e->getJobId() == job_id && e->getMachineId() == machine_id) {
                auto found_event = *it;
                event_queue.erase(it);
                delete found_event;
                break;
            }
            else {
                it++;
            }
        }
    };

    auto removeFromEventQueueAnyJob = [](EventType event_type, long machine_id, std::deque<Event*>& event_queue) {
        auto it = event_queue.begin();
        while (it != event_queue.end()) {
            if ((*it)->getEventType() != event_type) {
                it++;
                continue;
            }
            auto e = dynamic_cast<JobAndMachineEvent*>(*it);
            if (e->getMachineId() == machine_id) {
                auto found_event = *it;
                event_queue.erase(it);
                delete found_event;
                break;
            }
            else {
                it++;
            }
        }
    };

    auto findInEventQueueAnyJob = [](EventType event_type, long machine_id, std::deque<Event*>& event_queue) -> Event* {
        auto it = event_queue.begin();
        while (it != event_queue.end()) {
            if ((*it)->getEventType() != event_type) {
                it++;
                continue;
            }
            auto e = dynamic_cast<JobAndMachineEvent*>(*it);
            if (e->getMachineId() == machine_id) {
                return e;
            }
            else {
                it++;
            }
        }
        return nullptr;
    };

    for (const auto& pair : jobs) {
        addToEventQueue(new SystemEntry(pair.second->getReleaseTime(), pair.first), event_queue);
    }

    for (const auto& pair : topology->getTopologyElementsMap()) {
        for (auto breakdown : pair.second->getBreakdowns()) {
            addToEventQueue(new BreakdownStart(breakdown->getStartTime(), pair.first), event_queue);
            addToEventQueue(new BreakdownEnd(breakdown->getEndTime(), pair.first), event_queue);
        }
    }

    while (!event_queue.empty() || !wake_machines_queue.empty()) {

        if (!event_queue.empty() && (wake_machines_queue.empty() || event_queue.front()->getTime() == time)) {

            Event* event = event_queue.front();
            event_queue.pop_front();
            long event_time = event->getTime();
            time = event_time;

            switch (event->getEventType()) {

                case SYSTEM_ENTRY: {
                    auto system_entry_event = dynamic_cast<SystemEntry*>(event);
                    long job_id = system_entry_event->getJobId();
                    auto processing_step = job_route_map[job_id]->getNextProcessingStep();
                    job_processing_context_map[job_id]->setJobProcessingStep(processing_step);
                    long machine_id = processing_step->getMachineId();
                    long step_id = processing_step->getProcessingStepId();
                    addToEventQueue(new MachineBufferEntry(time, job_id, machine_id, step_id), event_queue);
                    break;
                }

                case SYSTEM_EXIT: {
                    auto system_exit_event = dynamic_cast<SystemExit*>(event);
                    long job_id = system_exit_event->getJobId();
                    auto job_processing_context = job_processing_context_map[job_id];
                    if (!job_processing_context->checkIfPathFinished()) {
                        throw SchedulingError("Path invalid for job " + std::to_string(job_id));
                    }
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
                    auto job = jobs.at(job_id);
                    long processing_duration = job->getProcessingTime(machine_id);
                    bool preempt = job->getJobType()->getPreempt();
                    if (topology->getTopologyElementsMap().at(machine_id)->getTopologyElementType() == MACHINE_TOPOLOGY_ELEMENT) {
                        preempt = preempt && ((Machine*)topology->getTopologyElementsMap().at(machine_id))->getMachineType()->getPreempt();
                    }
                    auto path_tree_node = job->getPathTreeNode(individual->getProcessingRoute(job_id)->getProcessingStep(step_id)->getPathNodeId());
                    if (path_tree_node->getPathNode()->getPrerequisites().empty()) {
                        machine_processing_context->addStepToBuffer(step_id, job_id, time, processing_duration, preempt);
                        wake_machines_queue.push(new WakeMachine(time, machine_id));
                    }
                    else {
                        machine_processing_context->addStepWaitingForPrerequisite(step_id, job_id, time, processing_duration, preempt);
                        addToEventQueue(new PrerequisitesWaitStart(time, job_id, machine_id, step_id), event_queue);
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
                    long processing_duration = machine_processing_context->getRemainingTimeForCurrent();
                    addToEventQueue(new MachineExit(time + processing_duration, job_id, machine_id, step_id), event_queue);
                    break;
                }

                case MACHINE_EXIT: {
                    auto machine_exit_event = dynamic_cast<MachineExit*>(event);
                    long job_id = machine_exit_event->getJobId();
                    long machine_id = machine_exit_event->getMachineId();
                    long step_id = machine_exit_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    auto job_route = job_route_map[job_id];
                    if (job_route->checkHasFinished()) {
                        job_processing_context_map[job_id]->setJobProcessingStep(nullptr);
                        addToEventQueue(new SystemExit(time, job_id), event_queue);
                    }
                    else {
                        auto processing_step = job_route->getNextProcessingStep();
                        job_processing_context_map[job_id]->setJobProcessingStep(processing_step);
                        long next_machine_id = processing_step->getMachineId();
                        long next_step_id = processing_step->getProcessingStepId();
                        addToEventQueue(new MachineBufferEntry(time, job_id, next_machine_id, next_step_id), event_queue);
                    }
                    machine_processing_context->finishProcessingAStep();
                    wake_machines_queue.push(new WakeMachine(time, machine_id));
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
                            it++;
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
                    for (auto machine_pair : topology->getTopologyElementsMap()) {
                        for (auto job_pair : jobs) {
                            job_processing_prerequisites->updatePrerequisites(machine_pair.first, job_pair.first, machine_to_job_times_processed_map[machine_pair.first][job_pair.first]);
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
                    long step_id = prerequisite_wait_end_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->moveStepFromWaitingToBuffer(job_id);
                    wake_machines_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case PREEMPT: {
                    auto preempt_event = dynamic_cast<Preempt*>(event);
                    long job_id = preempt_event->getJobId();
                    long machine_id = preempt_event->getMachineId();
                    long step_id = preempt_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->moveCurrentToBuffer(time);
                    removeFromEventQueue(MACHINE_EXIT, job_id, machine_id, event_queue);
                    wake_machines_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case BREAKDOWN_START: {
                    auto breakdown_start_event = dynamic_cast<BreakdownStart*>(event);
                    long machine_id = breakdown_start_event->getMachineId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->setCurrentlyInBreakdown();
                    if (machine_processing_context->getCurrentlyWorking()) {
                        auto [job_id, step_id] = machine_processing_context->getCurrentStepData();
                        if (machine_processing_context->checkCanPreemptCurrent()) {
                            addToEventQueue(new Preempt(time, job_id, machine_id, step_id), event_queue);
                        }
                        else {
                            addToEventQueue(new MachineExitForced(time, job_id, machine_id, step_id), event_queue);
                        }
                    }
                    if (machine_processing_context->getSetup()) {
                        auto processing_pair = machine_processing_context->peekAtFirstProcessingStep();
                        long step_id = processing_pair.first;
                        long job_id = processing_pair.second;
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
                    wake_machines_queue.push(new WakeMachine(time, machine_id));
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
                    long step_id = setup_cancel_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    removeFromEventQueue(SETUP_END, job_id, machine_id, event_queue);
                    machine_processing_context->setSetup(nullptr);
                    wake_machines_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case MACHINE_EXIT_FORCED: {
                    auto machine_exit_forced_event = dynamic_cast<MachineExitForced*>(event);
                    long job_id = machine_exit_forced_event->getJobId();
                    long machine_id = machine_exit_forced_event->getMachineId();
                    long step_id = machine_exit_forced_event->getStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    machine_processing_context->finishProcessingAStep();
                    removeFromEventQueue(MACHINE_EXIT, job_id, machine_id, event_queue);
                    addToEventQueue(new SystemExitForced(time, job_id), event_queue);
                    break;
                }
                case SYSTEM_EXIT_FORCED: {
                    auto system_exit_forced_event = dynamic_cast<SystemExitForced*>(event);
                    long job_id = system_exit_forced_event->getJobId();
                    break;
                }

                case ABSTRACT:
                    throw SchedulingError("Abstract event encountered in the event_queue in Simulator::simulate function.");

                case WAKE_MACHINE:
                    throw SchedulingError("Wake machine event encountered in the event_queue in Simulator::simulate function.");
            }

            if (enable_logging && !event->getMessage().empty()) {
                log_file << "[" << time << "] " << event->getMessage() << std::endl;
            }

            delete event;
        }

        else {

            auto event = wake_machines_queue.top();
            wake_machines_queue.pop();

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
                    throw SchedulingError("Non wake machine event encountered in the wake_machines_queue in Simulator::simulate function.");;

                case WAKE_MACHINE: {
                    auto wake_machine_event = dynamic_cast<WakeMachine*>(event);
                    long machine_id = wake_machine_event->getMachineId();
                    MachineProcessingContext* machine_processing_context = machine_processing_context_map[machine_id];
                    if (!machine_processing_context->hasReadyJobs() || machine_processing_context->isInBreakdown()) {
                        break;
                    }
                    if (!machine_processing_context->getCurrentlyWorking()) {
                        auto processing_pair = machine_processing_context->peekAtFirstProcessingStep();
                        long step_id = processing_pair.first;
                        long job_id = processing_pair.second;
                        auto setup = machine_processing_context->getSetup();
                        if (setup != nullptr) {
                            auto setup_end_event = dynamic_cast<SetupEnd*>(findInEventQueueAnyJob(SETUP_END, machine_id, event_queue));
                            if (setup_end_event != nullptr) {
                                long setup_step_id = setup_end_event->getStepId();
                                long setup_job_id = setup_end_event->getJobId();
                                bool should_cancel_setup = machine_processing_context->comparePrioritiesOfTwoSteps(step_id, setup_step_id);
                                if (should_cancel_setup) {
                                    addToEventQueue(new SetupCancel(time, setup_job_id, machine_id, setup_step_id, machine_processing_context->getSetup()), event_queue);
                                }
                            }
                            else {
                                throw SchedulingError("Setup start event without setup end event pair found in Simulator::simulate function.");
                            }
                            break;
                        }
                        auto topology_element = topology->getTopologyElementsMap().at(machine_id);
                        if (topology_element->getTopologyElementType() == MACHINE_TOPOLOGY_ELEMENT) {
                            auto machine = (Machine*) topology_element;
                            auto setup_rules = machine->getMachineType()->getSetupRules();
                            auto last_job_type = machine_processing_context->getLastJobType();
                            auto job_type = jobs.at(job_id)->getJobType();
                            auto new_setup = setup_rules->findSetup(last_job_type ? last_job_type->getId() : -1, job_type->getId());
                            if (new_setup) {
                                machine_processing_context->setSetup(new_setup);
                                addToEventQueue(new SetupStart(time, job_id, machine_id, step_id, new_setup), event_queue);
                                break;
                            }
                        }
                        addToEventQueue(new MachineEntry(time, job_id, machine_id, step_id), event_queue);
                    }
                    else if (machine_processing_context->checkShouldPreempt()) {
                        auto [job_id, step_id] = machine_processing_context->getCurrentStepData();
                        addToEventQueue(new Preempt(time, job_id, machine_id, step_id), event_queue);
                    }
                    break;
                }
            }

            delete event;
        }
    }

    log_file.close();
}