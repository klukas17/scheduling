//
// Created by mihael on 30/04/23.
//

#include "JobRoute.h"
#include "MachineNode.h"

JobRoute::JobRoute(Job* job, Individual* individual) {
    this->job = job;
    this->current_index = 0;
}

std::vector<long> JobRoute::getMachineList() {
    return machine_list;
}

void JobRoute::addMachineToMachineList(long machine_id) {
    machine_list.push_back(machine_id);
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