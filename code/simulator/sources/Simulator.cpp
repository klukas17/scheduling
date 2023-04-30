//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "Simulator.h"
#include "queue"
#include "fstream"
#include "MachineNode.h"
#include "MachineProcessingContext.h"
#include "Event.h"
#include "SystemEntry.h"
#include "SystemExit.h"
#include "MachineBufferEntry.h"
#include "WakeMachine.h"
#include "MachineEntry.h"
#include "MachineExit.h"

Simulator::Simulator() {}

void Simulator::simulate(Individual *individual, std::vector<Job *> jobs, std::string logs_path) {

    long time = 0;
    std::ofstream log_file(logs_path);
    std::queue<Event*> event_queue;
    std::queue<Event*> immediate_event_queue;
    std::map<long, MachineNode*> machine_map;

    MachineNode* root_node = (MachineNode*) individual->getRootNode();
    machine_map[root_node->getId()] = root_node;

    std::map<long, MachineProcessingContext*> machine_processing_context_map;
    machine_processing_context_map[root_node->getId()] = new MachineProcessingContext(root_node);

    std::map<long, Job*> job_map;
    for (Job* job : jobs) {
        job_map[job->getId()] = job;
    }

    for (Job* job : jobs) {
        immediate_event_queue.push(new SystemEntry(time, job->getId()));
    }

    while (!immediate_event_queue.empty() || !event_queue.empty()) {

        Event* event = nullptr;

        if (!immediate_event_queue.empty()) {
            event = immediate_event_queue.front();
            immediate_event_queue.pop();
        }

        else if (!event_queue.empty()) {
            event = event_queue.front();
            event_queue.pop();
            time += event->getTime();
        }

        switch (event->getEventType()) {

            case SYSTEM_ENTRY:
                immediate_event_queue.push(new MachineBufferEntry(0, ((SystemEntry*)event)->getJobId(), root_node->getId()));
                machine_processing_context_map[root_node->getId()]->addJobToBuffer(((SystemEntry*)event)->getJobId());
                break;

            case SYSTEM_EXIT:
                break;

            case MACHINE_BUFFER_ENTRY:
                immediate_event_queue.push(new WakeMachine(0, ((MachineBufferEntry*)event)->getMachineId()));
                break;

            case MACHINE_ENTRY:
                log_file << "[" << time << "] " << "Job " + std::to_string(((MachineEntry*)event)->getJobId()) + ": Started processing on Machine " + std::to_string(((MachineEntry*)event)->getMachineId()) << std::endl;
                event_queue.push(new MachineExit(job_map[((MachineEntry*)event)->getJobId()]->getProcessingTime(machine_processing_context_map[root_node->getId()]->getMachine()->getId()), ((MachineEntry*)event)->getJobId(), ((MachineEntry*)event)->getMachineId()));
                break;

            case MACHINE_EXIT:
                immediate_event_queue.push(new SystemExit(0, ((SystemExit*)event)->getJobId()));
                machine_processing_context_map[root_node->getId()]->decreaseJobsInBuffer();
                if (machine_processing_context_map[root_node->getId()]->getJobsInBuffer() > 0 && !machine_processing_context_map[root_node->getId()]->getCurrentlyWorking()) {
                    long job_id = machine_processing_context_map[root_node->getId()]->takeJobFromBuffer();
                    immediate_event_queue.push(new MachineEntry(0, job_id, machine_processing_context_map[root_node->getId()]->getMachine()->getId()));
                    machine_processing_context_map[root_node->getId()]->setCurrentlyWorking();
                }
                break;

            case WAKE_MACHINE:
                if (machine_processing_context_map[root_node->getId()]->getJobsInBuffer() > 0 && !machine_processing_context_map[root_node->getId()]->getCurrentlyWorking()) {
                    long job_id = machine_processing_context_map[root_node->getId()]->takeJobFromBuffer();
                    immediate_event_queue.push(new MachineEntry(0, job_id, machine_processing_context_map[root_node->getId()]->getMachine()->getId()));
                    machine_processing_context_map[root_node->getId()]->setCurrentlyWorking();
                }
                break;

            default:
                // todo:error
                break;
        }

        if (!event->getMessage().empty())
            log_file << "[" << time << "] " << event->getMessage() << std::endl;

        delete event;
    }

    log_file.close();
}