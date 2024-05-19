//
// Created by mihael on 5/5/24.
//

#include "SchedulingEvaluationFunction.h"
#include <utility>
#include "OnlineScheduler.h"
#include "OnlineSchedulingAlgorithmCluster.h"
#include "Simulator.h"

SchedulingEvaluationFunction::SchedulingEvaluationFunction(
    ObjectiveFunction* objective_function,
    Topology* topology,
    std::map<long, Job*>& jobs,
    bool logs_enabled,
    std::string output_dir
) : EvaluationFunction(true) {
    this->objective_function = objective_function;
    this->topology = topology;
    this->jobs = jobs;
    this->logs_enabled = logs_enabled;
    this->output_dir = std::move(output_dir);
    this->log_index = 0;
}

double SchedulingEvaluationFunction::_evaluate(Genotype* genotype) {
    log_index++;
    auto online_scheduling_algorithm_cluster = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(genotype);
    auto scheduler = new OnlineScheduler(online_scheduling_algorithm_cluster);
    auto simulator = new Simulator();
    scheduler->intializeJobContexts(jobs);
    auto simulator_statistics = simulator->simulate(scheduler, topology, jobs, logs_enabled, output_dir + "logs_" + std::to_string(log_index) + ".txt");
    auto result = objective_function->evaluate(simulator_statistics);
    delete scheduler;
    delete simulator;
    delete simulator_statistics;
    return result;
}
