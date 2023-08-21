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
#include "Event.h"
#include "SystemEntry.h"
#include "SystemExit.h"
#include "MachineBufferEntry.h"
#include "WakeMachine.h"
#include "MachineEntry.h"
#include "MachineExit.h"
#include "SchedulingError.h"

void Simulator::simulate(Individual *individual, Topology* topology, const std::map<long, Job *> &jobs, bool enable_logging, const std::string &logs_path) {

    long time = 0;
    std::ofstream log_file(logs_path);

    std::deque<Event*> event_queue;

    auto machine_map = individual->getGenotypeNodeMap();

    std::map<long, MachineProcessingContext*> machine_processing_context_map;
    for (auto entry : machine_map) {
        machine_processing_context_map[entry.first] = new MachineProcessingContext(entry.second);
    }

    auto job_route_map = individual->getProcessingRoutes();

    auto comparator = [topology] (WakeMachine* a, WakeMachine* b) {
        long id1 = a->getMachineId();
        long id2 = b->getMachineId();
        if (topology->getPriorityValue(id1, id2) == 1) return true;
        if (topology->getPriorityValue(id1, id2) == -1) return false;
        return true;
    };
    std::priority_queue<WakeMachine*, std::vector<WakeMachine*>, decltype(comparator)> wake_machines_queue(comparator);

    for (const auto& pair : jobs) {
        addToEventQueue(new SystemEntry(pair.second->getReleaseTime(), pair.first), event_queue);
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
                    long machine_id = processing_step->getMachineId();
                    long step_id = processing_step->getProcessingStepId();
                    auto machine_processing_context = machine_processing_context_map[machine_id];
                    addToEventQueue(new MachineBufferEntry(time, job_id, machine_id, step_id), event_queue);
                    machine_processing_context->addStepToBuffer(step_id, job_id);
                    break;
                }

                case SYSTEM_EXIT: {
                    auto system_exit_event = dynamic_cast<SystemExit*>(event);
                    break;
                }

                case MACHINE_BUFFER_ENTRY: {
                    auto machine_buffer_entry_event = dynamic_cast<MachineBufferEntry*>(event);
                    long machine_id = machine_buffer_entry_event->getMachineId();
                    long step_id = machine_buffer_entry_event->getStepId();
                    wake_machines_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case MACHINE_ENTRY: {
                    auto machine_entry_event = dynamic_cast<MachineEntry*>(event);
                    long job_id = machine_entry_event->getJobId();
                    long machine_id = machine_entry_event->getMachineId();
                    long step_id = machine_entry_event->getStepId();
                    long processing_duration = jobs.at(job_id)->getProcessingTime(machine_id);
                    if (enable_logging) {
                        log_file << "[" << time << "] " << "Job " << job_id << ": Started processing on Machine " << machine_id << " (step_id = " << step_id << ")" << std::endl;
                    }
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
                        addToEventQueue(new SystemExit(time, job_id), event_queue);
                    }
                    else {
                        auto processing_step = job_route->getNextProcessingStep();
                        long next_machine_id = processing_step->getMachineId();
                        long next_step_id = processing_step->getProcessingStepId();
                        auto next_machine_processing_context = machine_processing_context_map[next_machine_id];
                        addToEventQueue(new MachineBufferEntry(time, job_id, next_machine_id, next_step_id), event_queue);
                        next_machine_processing_context->addStepToBuffer(next_step_id, job_id);
                    }
                    machine_processing_context->decreaseStepsInBuffer();
                    machine_processing_context->unsetCurrentlyWorking();
                    wake_machines_queue.push(new WakeMachine(time, machine_id));
                    break;
                }

                case ABSTRACT:
                    throw SchedulingError("Abstract event encountered in Simulator::simulate function.");

                case WAKE_MACHINE:
                    throw SchedulingError("Wake machine event encountered in Simulator::simulate function.");
            }

            if (enable_logging && !event->getMessage().empty()) {
                log_file << "[" << time << "] " << event->getMessage() << std::endl;
            }

            delete event;
        }

        else {

            // WAKE_MACHINE
            auto wake_machine_event = wake_machines_queue.top();
            wake_machines_queue.pop();
            long machine_id = wake_machine_event->getMachineId();
            MachineProcessingContext* machine_processing_context = machine_processing_context_map[machine_id];
            if (machine_processing_context->getStepsInBuffer() > 0 && !machine_processing_context->getCurrentlyWorking()) {
                auto processing_pair = machine_processing_context->takeStepFromBuffer();
                long step_id = processing_pair.first;
                long job_id = processing_pair.second;
                addToEventQueue(new MachineEntry(time, job_id, machine_id, step_id), event_queue);
                machine_processing_context->setCurrentlyWorking();
            }

        }
    }

    log_file.close();
}

void Simulator::addToEventQueue(Event *event, std::deque<Event*> &event_queue) {
    auto it = std::upper_bound(event_queue.begin(), event_queue.end(), event, [](const Event* a, const Event* b) {
        return a->getTime() < b->getTime();
    });
    event_queue.insert(it, event);
}