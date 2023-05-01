//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SIMULATOR_H
#define SCHEDULING_SIMULATOR_H

#include "string"
#include "vector"
#include "Individual.h"
#include "Job.h"
#include "MachineNode.h"
#include "GenotypeNode.h"
#include "Event.h"
#include "deque"
#include "JobRoute.h"

class Simulator {
public:
    Simulator();
    static void simulate(Individual* individual, const std::map<long, Job*>& jobs, bool enable_logging = false, const std::string& logs_path = "");
    static void mapAllMachines(GenotypeNode* node, std::map<long, GenotypeNode*>& machine_map);
    static void addToEventQueue(Event* event, std::deque<Event*>& event_queue);
    static void fillJobRouteMachineLists(const std::map<long, JobRoute*>& job_route_map, GenotypeNode* node);
};


#endif //SCHEDULING_SIMULATOR_H
