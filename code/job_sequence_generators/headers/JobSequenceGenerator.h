//
// Created by mihael on 4/5/24.
//

#ifndef JOBSEQUENCEGENERATOR_H
#define JOBSEQUENCEGENERATOR_H

#include <map>
#include <vector>
#include "Job.h"
#include "JobGeneratorParameters.h"
#include "JobTypeMap.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

class JobSequenceGenerator {
    static UniformRealDistributionGenerator* chance_generator;
    static UniformIntDistributionGenerator* choice_generator;
public:
    static std::vector<Job*> generateJobs(
        std::map<long, JobGeneratorParameters*>& job_generator_parameters,
        TopologyElement* root_topology_element,
        JobTypeMap* job_type_map,
        double prerequisite_chance,
        double route_and_open_submachine_chance
    );
    static std::tuple<PathNode*, PathTreeNode*> generatePath(
        PathTreeNode* path_tree_node,
        double prerequisite_chance,
        double route_and_open_submachine_chance,
        std::vector<Job*>& jobs,
        const std::map<long, std::tuple<PathNode*, PathTreeNode*, std::set<long>>>& generator_data
    );
    static void connectGraphsOfPathNodes(
        PathNode* path_node,
        PathNode* next_path_node
    );
};


#endif //JOBSEQUENCEGENERATOR_H
