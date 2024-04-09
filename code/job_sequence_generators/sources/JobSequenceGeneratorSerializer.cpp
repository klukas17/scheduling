//
// Created by mihael on 4/9/24.
//

#include "JobSequenceGeneratorSerializer.h"
#include "fstream"
#include "GroupPathTreeNode.h"

void JobSequenceGeneratorSerializer::serializeJobs(const std::string& path, std::vector<Job*>& jobs) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "job_sequence";
    out << YAML::Value << YAML::BeginSeq;
    for (auto job : jobs) {
        serializeJob(out, job);
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;
    std::ofstream file(path);
    file << out.c_str();
    file.close();
}

void JobSequenceGeneratorSerializer::serializeJob(YAML::Emitter& out, Job* job) {
    out << YAML::BeginMap;
    out << YAML::Key << "job_id";
    out << YAML::Value << job->getId();
    out << YAML::Key << "job_type_id";
    out << YAML::Value << job->getJobType()->getId();
    out << YAML::Key << "release_time";
    out << YAML::Value << job->getReleaseTime();
    out << YAML::Key << "due_time";
    out << YAML::Value << job->getDueTime();
    out << YAML::Key << "weight";
    out << YAML::Value << job->getWeight();
    out << YAML::Key << "processing_route";
    out << YAML::Value << YAML::BeginSeq;
    serializePathNode(out, job->getPathsRootNode(), job->getPathsRootTreeNode());
    out << YAML::EndSeq;
    out << YAML::EndMap;
}

void JobSequenceGeneratorSerializer::serializePathNode(YAML::Emitter& out, PathNode* path_node, PathTreeNode* path_tree_node) {
    out << YAML::BeginMap;
    out << YAML::Key << "machine_id";
    out << YAML::Value << path_node->getTopologyElement()->getId();
    if (auto prerequisites = path_node->getPrerequisites(); !prerequisites.empty()) {
        out << YAML::Key << "prerequisites";
        out << YAML::Value << YAML::BeginSeq;
        for (auto const prerequisite : prerequisites) {
            out << YAML::BeginMap;
            out << YAML::Key << "job_id";
            out << YAML::Value << prerequisite->getJobId();
            out << YAML::Key << "machine_id";
            out << YAML::Value << prerequisite->getMachineId();
            out << YAML::Key << "repetitions";
            out << YAML::Value << prerequisite->getRepetitions();
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;
    }
    if (path_node->getTopologyElement()->getGeneralTopologyElementType() == GROUP_GENERAL_TOPOLOGY_ELEMENT) {
        out << YAML::Key << "sub_machines";
        out << YAML::Value << YAML::BeginSeq;
        for (auto const child : dynamic_cast<GroupPathTreeNode*>(path_tree_node)->getChildren()) {
            serializePathNode(out, child->getPathNode(), child);
        }
        out << YAML::EndSeq;
    }
    out << YAML::EndMap;
}
