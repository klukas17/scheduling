//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOBTYPE_H
#define SCHEDULING_JOBTYPE_H

#include <map>
#include <set>

#include "PathNode.h"
#include "PathTreeNode.h"

class JobType {
protected:
    long id;
    std::map<long, double> processing_times;
    std::set<long> forbidden_machine_types;
    bool preempt;
public:
    JobType(long id, bool preempt);
    [[nodiscard]] long getId() const;
    double getProcessingTime(long machine_type_id);
    void setProcessingTime(long machine_type_id, double processing_time);
    std::set<long> getForbiddenMachineTypes();
    void addForbiddenMachineType(long machine_type_id);
    [[nodiscard]] bool getPreempt() const;
    std::tuple<PathNode*, PathTreeNode*, std::set<long>> prepareDataForJobSequenceGenerator(TopologyElement* topology_element);
    static std::set<long> calculateIntersectionOfPaths(PathNode* path_node);
    std::tuple<PathNode*, PathTreeNode*> buildPaths(TopologyElement* topology_element);
    static void connectGraphsOfPathNodes(PathNode *path_node, PathNode *next_path_node);
};


#endif //SCHEDULING_JOBTYPE_H
