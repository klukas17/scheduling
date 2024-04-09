//
// Created by mihael on 4/5/24.
//

#include "JobSequenceGenerator.h"
#include <climits>

#include "Machine.h"
#include "MachinePathNode.h"
#include "MachinePathTreeNode.h"
#include "OpenGroup.h"
#include "OpenGroupPathNode.h"
#include "OpenGroupPathTreeNode.h"
#include "ParallelGroup.h"
#include "ParallelGroupPathNode.h"
#include "ParallelGroupPathTreeNode.h"
#include "RouteGroup.h"
#include "RouteGroupPathNode.h"
#include "RouteGroupPathTreeNode.h"
#include "SchedulingError.h"
#include "SerialGroup.h"
#include "SerialGroupPathNode.h"
#include "SerialGroupPathTreeNode.h"

UniformRealDistributionGenerator* JobSequenceGenerator::chance_generator = new UniformRealDistributionGenerator(0, 1);
UniformIntDistributionGenerator* JobSequenceGenerator::choice_generator = new UniformIntDistributionGenerator(0, INT_MAX);

std::vector<Job*> JobSequenceGenerator::generateJobs(
    std::map<long, JobGeneratorParameters*>& job_generator_parameters,
    TopologyElement* root_topology_element,
    JobTypeMap* job_type_map,
    double const prerequisite_chance,
    double const route_and_open_submachine_chance
) {

    std::vector<Job*> jobs;

    // release_time, job_type_id
    std::vector<std::tuple<double, long>> jobs_raw_data;

    for (auto [job_type_id, job_generator_param] : job_generator_parameters) {
        double time = 0;
        for (int i = 0; i < job_generator_param->getNumberOfJobs(); i++) {
            time += job_generator_param->generateReleaseTime();
            jobs_raw_data.emplace_back(time, job_type_id);
        }
    }

    std::sort(jobs_raw_data.begin(), jobs_raw_data.end());

    auto const generator_data = job_type_map->prepareDataForJobSequenceGenerator(root_topology_element);

    auto job_id = 0;

    for (auto [release_time, job_type_id] : jobs_raw_data) {
        auto const job_generator_params = job_generator_parameters[job_type_id];
        ++job_id;
        auto [path_node, path_tree_node] = generatePath(
            std::get<1>(generator_data.at(job_type_id)),
            prerequisite_chance,
            route_and_open_submachine_chance,
            jobs,
            generator_data
        );
        auto job = new Job(
            job_id,
            job_type_map->getJobType(job_type_id),
            path_node,
            path_tree_node,
            release_time,
            release_time + job_generator_params->getExpectedDuration(),
            job_generator_params->generateWeight()
        );
        jobs.push_back(job);
    }

    return jobs;
}

std::tuple<PathNode*, PathTreeNode*> JobSequenceGenerator::generatePath(
    PathTreeNode* path_tree_node,
    double const prerequisite_chance,
    double const route_and_open_submachine_chance,
    std::vector<Job*>& jobs,
    const std::map<long, std::tuple<PathNode*, PathTreeNode*, std::set<long>>>& generator_data
) {

    if (path_tree_node == nullptr) {
        return {nullptr, nullptr};
    }

    auto const path_node = path_tree_node->getPathNode();
    auto const topology_element = path_node->getTopologyElement();
    auto const topology_element_type = topology_element->getTopologyElementType();
    auto const machine_id = topology_element->getId();

    PathNode* generated_path_node;
    PathTreeNode* generated_path_tree_node;

    switch (topology_element_type) {

    case ABSTRACT_TOPOLOGY_ELEMENT:
        {
            throw SchedulingError("Abstract topology element of id " + std::to_string(machine_id) +  " found in JobType::buildPaths function.");
        }

    case MACHINE_TOPOLOGY_ELEMENT:
        {
            auto const machine_element = dynamic_cast<Machine*>(topology_element);
            auto const machine_path_node = new MachinePathNode(machine_id, machine_element);
            auto const machine_path_tree_node = new MachinePathTreeNode(machine_path_node);
            generated_path_node = machine_path_node;
            generated_path_tree_node = machine_path_tree_node;
            break;
        }

    case SERIAL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const serial_group_element = dynamic_cast<SerialGroup*>(topology_element);
            auto const serial_group_path_node = new SerialGroupPathNode(machine_id, serial_group_element);
            auto const serial_group_path_tree_node = new SerialGroupPathTreeNode(serial_group_path_node);
            std::vector<PathNode*> child_path_nodes;
            std::vector<PathTreeNode*> child_path_tree_nodes;
            for (auto const child_path_tree_node : dynamic_cast<SerialGroupPathTreeNode*>(path_tree_node)->getChildren()) {
                auto [generated_child_path_node, generated_child_path_tree_node] = generatePath(
                    child_path_tree_node,
                    prerequisite_chance,
                    route_and_open_submachine_chance,
                    jobs,
                    generator_data
                );
                child_path_nodes.push_back(generated_child_path_node);
                child_path_tree_nodes.push_back(generated_child_path_tree_node);
            }
            for (int i = 0; i < child_path_nodes.size() - 1; i++) {
                connectGraphsOfPathNodes(child_path_nodes[i], child_path_nodes[i + 1]);
            }
            connectGraphsOfPathNodes(serial_group_path_node, child_path_nodes[0]);
            for (auto const child : child_path_tree_nodes)
            {
                serial_group_path_tree_node->addChild(child);
            }
            generated_path_node = serial_group_path_node;
            generated_path_tree_node = serial_group_path_tree_node;
            break;
        }

    case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const parallel_group_element = dynamic_cast<ParallelGroup*>(topology_element);
            auto const parallel_group_path_node = new ParallelGroupPathNode(machine_id, parallel_group_element);
            auto const parallel_group_path_tree_node = new ParallelGroupPathTreeNode(parallel_group_path_node);
            for (auto const child_path_tree_node : dynamic_cast<ParallelGroupPathTreeNode*>(path_tree_node)->getChildren()) {
                auto [generated_path_node, generated_path_tree_node] = generatePath(
                    child_path_tree_node,
                    prerequisite_chance,
                    route_and_open_submachine_chance,
                    jobs,
                    generator_data
                );
                parallel_group_path_node->setNext(generated_path_node->getTopologyElement()->getId(), generated_path_node);
                parallel_group_path_tree_node->addChild(generated_path_tree_node);
            }
            generated_path_node = parallel_group_path_node;
            generated_path_tree_node = parallel_group_path_tree_node;
            break;
        }

    case ROUTE_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const route_group_element = dynamic_cast<RouteGroup*>(topology_element);
            auto const route_group_path_node = new RouteGroupPathNode(machine_id, route_group_element);
            auto const route_group_path_tree_node = new RouteGroupPathTreeNode(route_group_path_node);
            while (chance_generator->generate() < route_and_open_submachine_chance) {
                auto candidate_children = dynamic_cast<RouteGroupPathTreeNode*>(path_tree_node)->getChildren();
                if (!candidate_children.empty()) {
                    auto const index = choice_generator->generate() % candidate_children.size();
                    auto it = candidate_children.begin();
                    std::advance(it, index);
                    auto const child_path_tree_node = *it;
                    auto [generated_path_node, generated_path_tree_node] = generatePath(
                        child_path_tree_node,
                        prerequisite_chance,
                        route_and_open_submachine_chance,
                        jobs,
                        generator_data
                    );
                    route_group_path_node->addChild(generated_path_node, generated_path_node->getTopologyElement()->getId());
                    route_group_path_tree_node->addChild(generated_path_tree_node);
                }
            }
            generated_path_node = route_group_path_node;
            generated_path_tree_node = route_group_path_tree_node;
            break;
        }

    case OPEN_GROUP_TOPOLOGY_ELEMENT:
        {
            auto const open_group_element = dynamic_cast<OpenGroup*>(topology_element);
            auto const open_group_path_node = new OpenGroupPathNode(machine_id, open_group_element);
            auto const open_group_path_tree_node = new OpenGroupPathTreeNode(open_group_path_node);
            while (chance_generator->generate() < route_and_open_submachine_chance) {
                if (auto candidate_children = dynamic_cast<OpenGroupPathTreeNode*>(path_tree_node)->getChildren(); !candidate_children.empty()) {
                    auto const index = choice_generator->generate() % candidate_children.size();
                    auto it = candidate_children.begin();
                    std::advance(it, index);
                    auto const child_path_tree_node = *it;
                    auto [generated_path_node, generated_path_tree_node] = generatePath(
                        child_path_tree_node,
                        prerequisite_chance,
                        route_and_open_submachine_chance,
                        jobs,
                        generator_data
                    );
                    open_group_path_node->addChild(generated_path_node, generated_path_node->getTopologyElement()->getId());
                    open_group_path_tree_node->addChild(generated_path_tree_node);
                }
            }
            generated_path_node = open_group_path_node;
            generated_path_tree_node = open_group_path_tree_node;
            break;
        }
    }

    if (!jobs.empty()) {
        while (chance_generator->generate() < prerequisite_chance) {
            auto const job_id = choice_generator->generate() % jobs.size() + 1;
            auto const job = jobs[job_id - 1];
            auto const job_type_id = job->getJobType()->getId();
            auto const machines = std::get<2>(generator_data.at(job_type_id));
            if (!machines.empty()) {
                auto const index = choice_generator->generate() % machines.size();
                auto it = machines.begin();
                std::advance(it, index);
                auto const machine_id = *it;
                auto const prerequisite = new Prerequisite(job_id, machine_id, 1);
                generated_path_node->addPrerequisite(prerequisite);
            }
        }
    }

    return {generated_path_node, generated_path_tree_node};
}

void JobSequenceGenerator::connectGraphsOfPathNodes(PathNode* path_node, PathNode* next_path_node) {

    if (path_node == next_path_node) {
        return;
    }

    switch (path_node->getTopologyElement()->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in JobSequenceParser::connectGraphsOfJobPathNodes function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            {
                if (auto const machine_path_node = dynamic_cast<MachinePathNode*>(path_node); machine_path_node->getNext()) {
                    connectGraphsOfPathNodes(machine_path_node->getNext(), next_path_node);
                }
                else {
                    machine_path_node->setNext(next_path_node);
                }
                break;
            }

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const serial_group_path_node = dynamic_cast<SerialGroupPathNode*>(path_node); serial_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(serial_group_path_node->getNext(), next_path_node);
                }
                else {
                    serial_group_path_node->setNext(next_path_node);
                }
                break;
            }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const parallel_group_path_node = dynamic_cast<ParallelGroupPathNode*>(path_node); !parallel_group_path_node->getNext().empty()) {
                    for (auto [_, child] : parallel_group_path_node->getNext()) {
                        connectGraphsOfPathNodes(child, next_path_node);
                    }
                }
                else {
                    parallel_group_path_node->setNext(next_path_node->getTopologyElement()->getId(), next_path_node);
                }
                break;
            }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const route_group_path_node = dynamic_cast<RouteGroupPathNode*>(path_node); route_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(route_group_path_node->getNext(), next_path_node);
                }
                else {
                    route_group_path_node->setNext(next_path_node);
                }
                break;
            }

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            {
                if (auto const open_group_path_node = dynamic_cast<OpenGroupPathNode*>(path_node); open_group_path_node->getNext()) {
                    connectGraphsOfPathNodes(open_group_path_node->getNext(), next_path_node);
                }
                else {
                    open_group_path_node->setNext(next_path_node);
                }
                break;
            }
    }
}