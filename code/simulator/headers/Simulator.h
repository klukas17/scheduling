//
// Created by mihael on 29/04/23.
//

/**
 * @file Simulator.h
 * @brief Defines the Simulator class for simulating a schedule and its execution.
 */

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

/**
 * @class Simulator
 * @brief Simulates the execution of a schedule for scheduling optimization evaluation.
 *
 * The Simulator class is responsible for simulating the execution of a schedule (Individual) in a given topology
 * and with a set of jobs. It performs event-driven simulation to evaluate the schedule's performance and characteristics.
 */
class Simulator {
public:
    /**
     * @brief Simulates the execution of a schedule.
     * @param individual A pointer to the individual (schedule) to be simulated.
     * @param topology A pointer to the topology representing the environment.
     * @param jobs A map of job IDs to Job objects representing the jobs to be scheduled.
     * @param enable_logging Flag indicating whether to enable logging of simulation events.
     * @param logs_path The path where simulation logs will be saved if logging is enabled.
     */
    static void simulate(Individual* individual, Topology* topology, const std::map<long, Job*>& jobs, bool enable_logging = false, const std::string& logs_path = "");
};

#endif //SCHEDULING_SIMULATOR_H
