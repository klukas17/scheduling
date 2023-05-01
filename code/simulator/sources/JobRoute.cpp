//
// Created by mihael on 30/04/23.
//

#include "JobRoute.h"
#include "MachineNode.h"
#include "SerialGroupNode.h"
#include "ParallelGroupNode.h"
#include "RouteGroupNode.h"

JobRoute::JobRoute(Job* job, Individual* individual) {
    this->job_id = job->getId();
    this->job = job;
    this->current_index = 0;
    for (long machine_id : job->getProcessingRoute()) {
        machine_set.insert(machine_id);
    }
    this->fillMachineList(individual->getRootNode());
}

long JobRoute::getJobId() const {
    return job_id;
}

std::vector<long> JobRoute::getMachineList() {
    return machine_list;
}

void JobRoute::fillMachineList(GenotypeNode *node) {

    switch (node->getNodeType()) {

        case MACHINE_NODE_TYPE: {
            auto machine_node = (MachineNode*) node;
            machine_list.push_back(machine_node->getId());
            break;
        }

        case SERIAL_GROUP_NODE_TYPE: {
            auto serial_group_node = (SerialGroupNode*) node;
            machine_list.push_back(serial_group_node->getId());
            for (auto body_node : serial_group_node->getBody()) {
                this->fillMachineList(body_node);
            }
            break;
        }

        case PARALLEL_GROUP_NODE_TYPE: {
            auto parallel_group_node = (ParallelGroupNode*) node;
            machine_list.push_back(parallel_group_node->getId());
            bool body_machine_found = false;
            for (auto body_node : parallel_group_node->getBody()) {
                auto body_node_job_set = body_node->getJobSet();
                if (body_node_job_set.find(job_id) != body_node_job_set.end()) {
                    body_machine_found = true;
                    this->fillMachineList(body_node);
                    break;
                }
            }
            if (!body_machine_found) {
                // todo:error
            }
            break;
        }

        case ROUTE_GROUP_NODE_TYPE: {
            auto route_group_node = (RouteGroupNode*) node;
            machine_list.push_back(route_group_node->getId());
            for (auto body_node : route_group_node->getBody()) {
                if (this->machine_set.find(body_node->getId()) != this->machine_set.end()) {
                    this->fillMachineList(body_node);
                }
            }
        }

        default: {
            // todo:error
            break;
        }
    }
}

long JobRoute::getNextMachine() {
    long index = current_index;
    current_index++;
    return machine_list[index];
}

long JobRoute::getCurrentIndex() const {
    return current_index;
}

bool JobRoute::checkHasFinished() {
    return current_index == machine_list.size();
}