//
// Created by mihael on 8/19/23.
//

#ifndef SCHEDULING_PATHNODEUTILS_H
#define SCHEDULING_PATHNODEUTILS_H

#include "Job.h"
#include "string"
#include "deque"

class PathNodeUtils {
public:
    static void logPathNodes(const std::map<long, Job*>& jobs, const std::string& logs_path);
    static void logPathNode(PathNode* path_node, std::deque<long>& path_node_deque, std::ofstream& log_stream);
};

#endif //SCHEDULING_PATHNODEUTILS_H
