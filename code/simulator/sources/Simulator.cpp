//
// Created by mihael on 29/04/23.
//

#include <algorithm>
#include "Simulator.h"
#include "queue"
#include "fstream"
#include "MachineNode.h"
#include "SerialGroupNode.h"
#include "ParallelGroupNode.h"
#include "MachineProcessingContext.h"
#include "JobRoute.h"
#include "Event.h"
#include "SystemEntry.h"
#include "SystemExit.h"
#include "MachineBufferEntry.h"
#include "WakeMachine.h"
#include "MachineEntry.h"
#include "MachineExit.h"

Simulator::Simulator() = default;

void Simulator::simulate(Individual *individual, const std::map<long, Job *> &jobs, bool enable_logging, const std::string &logs_path) {

    long time = 0;
    std::ofstream log_file(logs_path);

    std::deque<Event*> event_queue;

    std::map<long, GenotypeNode*> machine_map;
    mapAllMachines(individual->getRootNode(), machine_map);

    std::map<long, MachineProcessingContext*> machine_processing_context_map;
    for (auto entry : machine_map) {
        machine_processing_context_map[entry.first] = new MachineProcessingContext(entry.second);
    }

    std::map<long, JobRoute*> job_route_map;
    for (const auto& pair : jobs) {
        job_route_map[pair.first] = new JobRoute(pair.first, individual);
    }

    std::map<long, std::map<long, long>> job_processing_times;
    for (const auto& pair : jobs) {
        long job_id = pair.first;
        for (auto machine_id : job_route_map[job_id]->getMachineList()) {
            if (machine_map[machine_id]->getNodeType() == MACHINE_NODE_TYPE) {
                auto machine_node = (MachineNode*) machine_map[machine_id];
                job_processing_times[job_id][machine_id] = jobs.find(job_id)->second->getProcessingTime(machine_node->getMachineType()->getId());
            }
            else {
                job_processing_times[job_id][machine_id] = 0;
            }
        }
    }

    for (const auto& pair : jobs) {
        addToEventQueue(new SystemEntry(time, pair.first), event_queue);
    }

    while (!event_queue.empty()) {

        Event* event = event_queue.front();
        event_queue.pop_front();
        long event_time = event->getTime();
        time = event_time;

        switch (event->getEventType()) {

            case SYSTEM_ENTRY: {
                auto system_entry_event = dynamic_cast<SystemEntry*>(event);
                long job_id = system_entry_event->getJobId();
                long next_machine_id = job_route_map[job_id]->getNextMachine();
                auto machine_processing_context = machine_processing_context_map[next_machine_id];
                addToEventQueue(new MachineBufferEntry(time, job_id, next_machine_id), event_queue);
                machine_processing_context->addJobToBuffer(job_id);
                break;
            }

            case SYSTEM_EXIT: {
                auto system_exit_event = dynamic_cast<SystemExit*>(event);
                break;
            }

            case MACHINE_BUFFER_ENTRY: {
                auto machine_buffer_entry_event = dynamic_cast<MachineBufferEntry*>(event);
                long machine_id = machine_buffer_entry_event->getMachineId();
                addToEventQueue(new WakeMachine(time, machine_id), event_queue);
                break;
            }

            case MACHINE_ENTRY: {
                auto machine_entry_event = dynamic_cast<MachineEntry*>(event);
                long job_id = machine_entry_event->getJobId();
                long machine_id = machine_entry_event->getMachineId();
                long processing_duration = job_processing_times[job_id][machine_id];
                if (enable_logging) {
                    log_file << "[" << time << "] " << "Job " << job_id << ": Started processing on Machine " << machine_id << std::endl;
                }
                addToEventQueue(new MachineExit(time + processing_duration, job_id, machine_id), event_queue);
                break;
            }

            case MACHINE_EXIT: {
                auto machine_exit_event = dynamic_cast<MachineExit*>(event);
                long job_id = machine_exit_event->getJobId();
                long machine_id = machine_exit_event->getMachineId();
                auto machine_processing_context = machine_processing_context_map[machine_id];
                auto job_route = job_route_map[job_id];
                if (job_route->checkHasFinished()) {
                    addToEventQueue(new SystemExit(time, job_id), event_queue);
                }
                else {
                    long next_machine_id = job_route->getNextMachine();
                    auto next_machine_processing_context = machine_processing_context_map[next_machine_id];
                    addToEventQueue(new MachineBufferEntry(time, job_id, next_machine_id), event_queue);
                    next_machine_processing_context->addJobToBuffer(job_id);
                }
                machine_processing_context->decreaseJobsInBuffer();
                machine_processing_context->unsetCurrentlyWorking();
                if (machine_processing_context->getJobsInBuffer() > 0 && !machine_processing_context->getCurrentlyWorking()) {
                    long new_job_id = machine_processing_context->takeJobFromBuffer();
                    addToEventQueue(new MachineEntry(time, new_job_id, machine_id), event_queue);
                    machine_processing_context->setCurrentlyWorking();
                }
                break;
            }

            case WAKE_MACHINE: {
                auto wake_machine_event = dynamic_cast<WakeMachine*>(event);
                long machine_id = wake_machine_event->getMachineId();
                MachineProcessingContext* machine_processing_context = machine_processing_context_map[machine_id];
                if (machine_processing_context->getJobsInBuffer() > 0 && !machine_processing_context->getCurrentlyWorking()) {
                    long job_id = machine_processing_context->takeJobFromBuffer();
                    addToEventQueue(new MachineEntry(time, job_id, machine_id), event_queue);
                    machine_processing_context->setCurrentlyWorking();
                }
                break;
            }

            default: {
                // todo:error
                break;
            }

        }

        if (enable_logging && !event->getMessage().empty()) {
            log_file << "[" << time << "] " << event->getMessage() << std::endl;
        }

        delete event;
    }

    log_file.close();
}

void Simulator::mapAllMachines(GenotypeNode *node, std::map<long, GenotypeNode *> &machine_map) {

    switch (node->getNodeType()) {

        case MACHINE_NODE_TYPE: {
            auto machine_node = (MachineNode*) node;
            machine_map[machine_node->getId()] = machine_node;
            break;
        }

        case SERIAL_GROUP_NODE_TYPE: {
            auto serial_group_node = (SerialGroupNode*) node;
            machine_map[serial_group_node->getId()] = serial_group_node;
            for (auto body_element : serial_group_node->getBody()) {
                mapAllMachines(body_element, machine_map);
            }
            break;
        }

        case PARALLEL_GROUP_NODE_TYPE: {
            auto parallel_group_node = (ParallelGroupNode*) node;
            machine_map[parallel_group_node->getId()] = parallel_group_node;
            for (auto body_element : parallel_group_node->getBody()) {
                mapAllMachines(body_element, machine_map);
            }
            break;
        }

        default: {
            // todo: error
            break;
        }
    }
}

void Simulator::addToEventQueue(Event *event, std::deque<Event*> &event_queue) {
    auto it = std::upper_bound(event_queue.begin(), event_queue.end(), event, [](const Event* a, const Event* b) {
        return a->getTime() < b->getTime();
    });
    event_queue.insert(it, event);
}