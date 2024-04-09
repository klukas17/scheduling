//
// Created by mihael on 4/9/24.
//

#ifndef JOBSEQUENCEGENERATORSERIALIZER_H
#define JOBSEQUENCEGENERATORSERIALIZER_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "Job.h"


class JobSequenceGeneratorSerializer {
public:
    static void serializeJobs(const std::string& path, std::vector<Job*>& jobs);
    static void serializeJob(YAML::Emitter& out, Job* job);
    static void serializePathNode(YAML::Emitter& out, PathNode* path_node, PathTreeNode* path_tree_node);
};



#endif //JOBSEQUENCEGENERATORSERIALIZER_H
