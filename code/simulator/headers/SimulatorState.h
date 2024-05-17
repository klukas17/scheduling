//
// Created by mihael on 5/11/24.
//

#ifndef SIMULATORSTATE_H
#define SIMULATORSTATE_H

#include <map>
#include "Job.h"
#include "SimulatorStateJobInfo.h"
#include "Topology.h"


class SimulatorState {
    double time;
    std::map<long, Job*> jobs;
    Topology* topology;
    std::map<long, SimulatorStateJobInfo*> job_info_map;
    // machine_id -> job_ids
    std::map<long, std::set<long>> jobs_in_machines_map;
    // machine_id -> number_of_jobs_passed
    std::map<long, int> branch_passing_map;
public:
    SimulatorState(const std::map<long, Job*>& jobs, Topology* topology);
    double getTime();
    void setTime(double time);
    Job* getJob(long job_id);
    void setJobOnMachine(long machine_id, long job_id);
    void machineEntry(long machine_id, long job_id, double remaining_time_on_machine);
    void machineExit(long machine_id, long job_id);
    void machineBufferEntry(long machine_id, long job_id, double remaining_time_on_machine);
    void preempt(long machine_id, long job_id, double remaining_time_on_machine);
    double calculateCombinedWeightsOfBatchCompatibleJobs(long machine_id, long job_id);
    int calculateNumberOfBatchCompatibleJobs(long machine_id, long job_id);
    std::vector<Job*> calculateBatchCompatibleJobs(long machine_id, long job_id);
    void addBranchPassingPoint(long machine_id);
    int getNumberOfBranchPassings(long machine_id);
    int calculateNumberOfJobsInBranch(long machine_id);
    double calculateRemainingProcessingTimeInBranch(PathNode* path_node);
    double calculateRemainingProcessingTimeForPathNode(PathNode* path_node, PathNode* prev_path_node, double diff);
};



#endif //SIMULATORSTATE_H
